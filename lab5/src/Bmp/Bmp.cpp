#include "Bmp.h"

BMP::BMP(const std::string & file_path) : m_row_stride{0} {
    load(file_path);
}

BMP::BMP(int32_t width, int32_t height, bool has_alpha) {
    // проверяем заданную ширину и высоту
    if (width <= 0 || height <= 0) throw std::runtime_error("The image width and height must be positive numbers.");

    // записываем ширину
    m_info_header.width = width;

    // записываем высоту
    m_info_header.height = height;

    // если задано 4 канала (32-битное изображение)
    if (has_alpha) {
        // записываем размер информационного хэдера (InfoHeader и ColorHeader относятся к информационному хэдеру)
        m_info_header.size = sizeof(InfoHeader) + sizeof(ColorHeader);

        // записываем, через сколько байт от начала файла начинаются пиксели
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader) + sizeof(ColorHeader);

        // записываем, что на пиксель приходится 32 бита информации
        m_info_header.bit_count = 32;

        // записываем, что изображение не сжатое
        m_info_header.compression = 3;

        // вычисляем количество значимых байт
        m_row_stride = width * 4;

        // выделям память для хранения информации о пикселях (ширина * высота * количество каналов)
        m_data.resize(m_row_stride * height);

        // записываем размер файла (служебная информация + информация о пикселях)
        m_file_header.file_size = m_file_header.offset_data + m_data.size();
    }
    // если задано 3 канала (24-битное изображение)
    else {
        // записываем размер информационного хэдера
        m_info_header.size = sizeof(InfoHeader);

        // записываем, через сколько байт от начала файла начинаются пиксели
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader);

        // записываем битность изображения
        m_info_header.bit_count = 24;

        // записываем способ хранения информации о пикселях
        m_info_header.compression = 0;

        // записывем количество значимых байт
        m_row_stride = width * 3;

        // выделяем память для информации о пикселях
        m_data.resize(m_row_stride * height);

        // вычисляем длину строки для выравнивания
        uint32_t new_stride{_makeStrideAligned(4)};

        // записыаем размер файла
        m_file_header.file_size = m_file_header.offset_data + m_data.size() +
                                  m_info_header.height * (new_stride - m_row_stride);
    }
}

void BMP::load(const std::string & file_path) {
    // открываем файловый поток в бинарном режиме
    std::ifstream input{file_path, std::ios::binary};

    // проверяем, открылся ли файл
    if (!input) throw std::runtime_error("Unable to open the input image file!");
    // считываем заголовочную структуру изображения
    input.read((char*)&m_file_header, sizeof(m_file_header));

    // проверяем формат изображения
    if (m_file_header.file_type != 0x4D42) throw std::runtime_error("Unrecognized file format!");

    // считываем информационный хэдер
    input.read((char*)&m_info_header, sizeof(m_info_header));

    // если изображение 32-битное, нужно проверить и считать ColorHeader
    if (m_info_header.bit_count == 32) {
        // проверям содержит ли файл ColorHeader (записывается только в 32-битные изображения)
        if (m_info_header.size >= (sizeof(InfoHeader) + sizeof(ColorHeader))) {
            // считываем ColorHeader
            input.read((char*)&m_color_header, sizeof(m_color_header));

            // проверяем, записаны ли пиксели в формате BGRA и является ли цветовое пространство sRGB
            _checkColorHeader(m_color_header);
        }
        // если не содержит - выбрасываем исключение
        else {
            std::cerr << "Warning! The file \"" << file_path << "\" does not seem to contain bit mask information\n";
            throw std::runtime_error("Error! Unrecognized file format!");
        }
    }

    // перемещаемся к началу пикселей
    input.seekg(m_file_header.offset_data, std::ifstream::beg);

    // в силу того, что некоторые фоторедакторы помещают в файл служебную информацию, которую можно спокойно игнорировать,
    // чтобы ничего не сбилось, нужно настроить размер информационного хэдера, размер файла и указать, откуда начинаются пиксели

    // если изображение 32-битное
    if (m_info_header.bit_count == 32) {
        // записываем размер информационного хэдера, учитывая ColorHeader
        m_info_header.size = sizeof(InfoHeader) + sizeof(ColorHeader);

        // записываем, через сколько байт от начала файла начинаются пиксели, учитывая ColorHeader
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader) + sizeof(ColorHeader);
    }
    // если изображение 24-битное
    else {
        // записываем размер информационного хэдера
        m_info_header.size = sizeof(InfoHeader);

        // записываем, через сколько байт от начала файла начинаются пиксели
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader);
    }
    // записываем размер файла (это не весь размер файла, а лишь то,
    // сколько занимают заголовочные структуры и служебная информация)
    m_file_header.file_size = m_file_header.offset_data;

    // если высота изображения задается отрицательным числом,
    // то отсчет пикселей ведется сверху-вниз, начиная в верхнем левом углу

    // если высота изображения задается положительным числом,
    // то отсчет пикселей ведется снизу-вверх, начиная в нижнем левом углу

    // данная программа берет за начало отсчета нижний левый угол

    // проверям высоту
    if (m_info_header.height < 0)
        throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");

    // выделям память для хранения информации о пикселях (ширина * высота * количество каналов)
    m_data.resize(m_info_header.width * m_info_header.height * m_info_header.bit_count / 8);

    // Формат изображения BMP предполагает, что каждая строка данных будет выровнена по границе четырех байтов или
    // дополнена нулями, если это не так. Для изображения с разрешением 32 бита на пиксель условие выравнивания всегда выполняется.
    // В случае изображений с разрешением 24 бита на пиксель условие выравнивания выполняется только в том случае,
    // если ширина изображения делится на 4, в противном случае нам нужно будет заполнить строки нулями.

    // если ширина изображения делится на 4
    if (m_info_header.width % 4 == 0) {
        // считываем информацию о пикселях
        input.read((char*)m_data.data(), m_data.size());

        // обновляем размер файла (добавляем к нему то, сколько занимает информация о пикселях)
        m_file_header.file_size += m_data.size();
    }
    // если ширина изображения не делится на 4
    else {
        // вычисляем width
        // (количество пикселей в строке * количество каналов = количество байт в строке (width))
        m_row_stride = m_info_header.width * m_info_header.bit_count / 8;

        // вычисляем line_stride
        uint32_t new_stride{_makeStrideAligned(4)};

        // выделяем память для отступа (line_padding)
        std::vector<uint8_t> padding_row(new_stride - m_row_stride);

        // проходимся по каждой строке пикселей
        for (int y = 0; y < m_info_header.height; ++y) {
            // считываем информацию об отступе в информацию о пикселях
            // m_data.data() - начало отсчета
            // m_row_stride - сколько нужно отсупить, чтобы попасть на начало отступа
            // y - поскольку в памяти компьютера информация хранится в виде последовательности байт (как одномерный массив),
            //     смена строки пикселей производится через умножение

            // изначально имеем пустой вектор m_data
            // сперва считываем в него информацию о имеющихся пикселях
            input.read((char*)(m_data.data() + m_row_stride * y), m_row_stride);

            // есть два варианта, как поступить с отступом:
            // 1) считать незначащие нули
            // 2) программно переместить указатель на следующую строку

            // потом считываем отступ
            input.read((char*)padding_row.data(), padding_row.size());
        }

        // обновляем размер файла (размер пикселей + высота изображения * размер отступа)
        m_file_header.file_size += m_data.size() + m_info_header.height * padding_row.size();
    }
}

void BMP::save(const std::string & file_path) {
    // открываем файловый поток в бинарном режиме
    std::ofstream output{file_path, std::ios::binary};

    // проверяем, открылся ли файл
    if (!output) throw std::runtime_error("Unable to open the input image file!");

    // если изображение 32-битное
    if (m_info_header.bit_count == 32) {
        _writeHeadersAndData(output);
    }
    // если изображение 24-битное
    else if (m_info_header.bit_count == 24) {
        // ели ширина изображения делится на 4
        if (m_info_header.width % 4 == 0) {
            // записываем всю информацию об изображении
            _writeHeadersAndData(output);
        }
        // ели ширина изображения не делится на 4
        else {
            // вычисляем line_stride
            uint32_t new_stride{_makeStrideAligned(4)};

            // выделяем память для отступа (line_padding)
            std::vector<uint8_t> padding_row(new_stride - m_row_stride);

            // записываем только хэдеры
            _writeHeaders(output);

            for (int y = 0; y < m_info_header.height; ++y) {
                // записывем информацию о пикселях
                output.write((const char*)(m_data.data() + m_row_stride * y), m_row_stride);

                // записываем отступ
                output.write((const char*)padding_row.data(), padding_row.size());
            }
        }
    }
    // выбрасываем исключение (данная программа обрабатывает только 24- или 32-битные изображения)
    else {
        throw std::runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
    }
}

void BMP::fillRegion(uint32_t x0, uint32_t y0, uint32_t width, uint32_t height,
                     uint8_t R, uint8_t G, uint8_t B, uint8_t A) {

    // проверяем полученные данные, чтобы они соответствовали текущему изображению
    if (x0 + width > (uint32_t)m_info_header.width || y0 + height > (uint32_t)m_info_header.height)
        throw std::runtime_error("The region does not fit in the image!");

    // вычисляем количество каналов (глубина цвета / 8)
    uint32_t channels = m_info_header.bit_count / 8;

    // проходимся по пикселям заданной области
    for (uint32_t y = y0; y < y0 + height; ++y) {
        for (uint32_t x = x0; x < x0 + width; ++x) {

            // задаем цвет каждого отдельного пикселя в формате BGRA
            m_data.at(channels * (y * m_info_header.width + x) + 0) = B;
            m_data.at(channels * (y * m_info_header.width + x) + 1) = G;
            m_data.at(channels * (y * m_info_header.width + x) + 2) = R;

            // если имеем 4 канала (32-битное изображение)
            if (channels == 4) {
                // задаем компонент прозрачности
                m_data.at(channels * (y * m_info_header.width + x) + 3) = A;
            }
        }
    }
}

void BMP::scale(int32_t new_width, int32_t new_height) {
    // вычисляем соотношение ширины исходного изображения к новой ширине
    uint32_t x_ratio = ((m_info_header.width << 16) / new_width) + 1;

    // вычисляем соотношение высоты исходного изображения к новой высоте
    uint32_t y_ratio = ((m_info_header.height << 16) / new_height) + 1;

    // вычисляем количество каналов
    uint32_t channels = m_info_header.bit_count / 8;

    // выделяем память для информации о пикселях
    std::vector<uint8_t> temp(new_width * new_height * channels);

    uint32_t x_2{}, y_2{};
    for (uint32_t i = 0; i < new_height; ++i) {
        for (uint32_t j = 0; j < new_width; ++j) {
            // вычисляем позицию соседнего пикселя по оси x
            x_2 = ((j * x_ratio) >> 16);

            // вычисляем позицию соседнего пикселя по оси y
            y_2 = ((i * y_ratio) >> 16);

            // переносим необходимые пиксели в новый вектор
            temp[channels * (i * new_width + j) + 0] = m_data[channels * (y_2 * m_info_header.width + x_2) + 0];
            temp[channels * (i * new_width + j) + 1] = m_data[channels * (y_2 * m_info_header.width + x_2) + 1];
            temp[channels * (i * new_width + j) + 2] = m_data[channels * (y_2 * m_info_header.width + x_2) + 2];

            if (channels == 4) {
                temp[channels * (i * new_width + j) + 3] = m_data[channels * (y_2 * m_info_header.width + x_2) + 3];
            }
        }
    }

    // обновляем информацию об изображении
    m_info_header.width = new_width;
    m_info_header.height = new_height;
    m_data = temp;
}

void BMP::_checkColorHeader(ColorHeader &color_header) {
    ColorHeader expected_color_header{};

    // проверяем формат цвета, чтобы он соответствовал BGRA формату
    if (expected_color_header.red_mask   != color_header.red_mask   ||
        expected_color_header.blue_mask  != color_header.blue_mask  ||
        expected_color_header.green_mask != color_header.green_mask ||
        expected_color_header.alpha_mask != color_header.alpha_mask) {

        throw std::runtime_error("Unexpected color mask format! "
                                 "The program expects the pixel data to be in the BGRA format!");
    }

    // проверяем цветовое пространство, чтобы оно соответствовало sRGB
    if (expected_color_header.color_space_type != color_header.color_space_type) {
        throw std::runtime_error("Unexpected color space type! The program expects sRGB values");
    }
}

uint32_t BMP::_makeStrideAligned(uint32_t align_stride) const {
    // берем текущее количество байт в строке
    uint32_t new_stride{m_row_stride};

    // увеличиваем до тех пор, пока не будет делиться на 4
    while (new_stride % align_stride != 0) ++new_stride;

    return new_stride;
}

void BMP::_writeHeaders(std::ofstream &stream) {
    // записываем в файл заголовочную структуру изображения
    stream.write((const char*)&m_file_header, sizeof(m_file_header));

    // записываем в файл информационную структуру изображения
    stream.write((const char*)&m_info_header, sizeof(m_info_header));

    // если изображение 32-битное
    if (m_info_header.bit_count == 32) {
        // записываем в файл ColorHeader
        stream.write((const char*)&m_color_header, sizeof(m_color_header));
    }
}

void BMP::_writeHeadersAndData(std::ofstream &stream) {
    // записываем хэдеры
    _writeHeaders(stream);

    // записываем в файл информацию о пикселях
    stream.write((const char*)m_data.data(), m_data.size());
}

int32_t BMP::getWidth() const {
    return m_info_header.width;
}

int32_t BMP::getHeight() const {
    return m_info_header.height;
}

int32_t BMP::getImageSize() const {
    return m_info_header.size_image;
}

int32_t BMP::getBitCount() const {
    return m_info_header.bit_count;
}

int32_t BMP::getOffsetData() const {
    return m_file_header.offset_data;
}

int32_t BMP::getDataSizeBit() const {
    return this->getWidth() * this->getHeight() * this->getBitCount();
}

int32_t BMP::getDataSizeByte() const {
    return this->getDataSizeBit() / 8;
}

std::vector<BMP::RGBColor> BMP::getPixelsRGB() {
    std::vector<BMP::RGBColor> pixelsRGB{};

    uint32_t channels = m_info_header.bit_count / 8;

    for (uint32_t y = 0; y < this->getHeight(); ++y) {
        for (uint32_t x = 0; x < this->getWidth(); ++x) {
            BMP::RGBColor color{};
            color.R = (int)m_data.at(channels * (y * m_info_header.width + x) + 0);
            color.G = (int)m_data.at(channels * (y * m_info_header.width + x) + 1);
            color.B = (int)m_data.at(channels * (y * m_info_header.width + x) + 2);

            // // если имеем 4 канала (32-битное изображение)
            // if (channels == 4) {
            //     // задаем компонент прозрачности
            //     m_data.at(channels * (y * m_info_header.width + x) + 3) = A;
            // }
            pixelsRGB.push_back(color);
        }
    }
        // std::cout << "uint8_t color R: " << int(this->m_data.at(channels * y + 0)) << std::endl;
        // std::cout << "uint8_t color G: " << int(this->m_data.at(channels * y + 1)) << std::endl;
        // std::cout << "uint8_t color B: " << int(this->m_data.at(channels * y + 2)) << std::endl;
        // std::cout << std::endl;
    
    return pixelsRGB;
}

void BMP::printImage(std::vector<BMP::RGBColor> pixelsRGB) const {
    std::cout << "start printImage" << std::endl;
    std::cout << "width: " << this->getWidth() << std::endl;
    std::cout << "height: " << this->getHeight() << std::endl;

    uint32_t channels = m_info_header.bit_count / 8;

    for (uint32_t y = 0; y < this->getHeight(); ++y) {
        // std::cout << "hello " << std::endl;
        for (uint32_t x = 0; x < this->getWidth(); ++x) {
            // std::cout << "x:" << x << " y:" << y << std::endl;

            // задаем цвет каждого отдельного пикселя в формате BGRA
            int R = pixelsRGB[(int)this->getHeight() * y + x + 0].R;
            int G = pixelsRGB[(int)this->getHeight() * y + x + 1].G;
            int B = pixelsRGB[(int)this->getHeight() * y + x + 2].B;

            // // если имеем 4 канала (32-битное изображение)
            // if (channels == 4) {
            //     // задаем компонент прозрачности
            //     m_data.at(channels * (y * m_info_header.width + x) + 3) = A;
            // }

            Color::Modifier color(Color::FG_GREEN);
            Color::Modifier def(Color::FG_DEFAULT);
            // std::cout << "R:" << R << " ";
            // std::cout << "G:" << G << " ";
            // std::cout << "B:" << B << " " << std::endl;

            int threshold = 10;
            if (R < threshold && G < threshold && B < threshold) {
                Color::Modifier color(Color::FG_DEFAULT);
            } else if (R > G && R > B) {
                color = Color::FG_RED;
                // std::cout << "Red";
            } else if (G > R && G > B) {
                color = Color::FG_GREEN;
                // std::cout << "Green";
            } else {
                color = Color::FG_BLUE;
                // std::cout << "Blue";
            }

            char symbol = '#';

            if (!(R < threshold && G < threshold && B < threshold)) {
                std::cout << color << symbol << " " << def;
            } else {
                std::cout << def << symbol << " " << def;
            }
            // std::cout << "This ->" << color << "*" << def << "<- is red." << std::endl;
            // cout << "This ->" << red << "*" << def << "<- is red." << endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
