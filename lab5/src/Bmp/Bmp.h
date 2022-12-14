#ifndef BMP_H
#define BMP_H

#include "colormod.h"
#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <string>

class BMP {
public:
    struct RGBColor {
        int R {};
        int G {};
        int B {};
    };
    /// Конструктор с параметрами. Загружает растровое изображение с диска
    /// @param file_path путь к файлу изображения с расширением bmp
    explicit BMP(const std::string & file_path);

    /// Конструктор с параметрами. Создает растровое изображение
    /// @param width - ширина растрового изображения
    /// @param height - высота растрового изображения
    /// @param has_alpha - наличие канала прозрачности
    BMP(int32_t width, int32_t height, bool has_alpha = true);

    /// Загрузка растрового изображения с диска
    /// @param file_path - путь для загрузки
    void load(const std::string & file_path);

    /// Сохранение растрового изображения на диск
    /// @param file_path - путь для записи
    void save(const std::string & file_path);

    /// Заполнение указанной области указанным цветом
    /// @param x0 - координата для начала отсчета по оси x
    /// @param y0 - координата для начала отсчета по оси y
    /// @param width - ширина заполняемой области
    /// @param height - высота заполняемой области
    /// @param R - значение канала красного
    /// @param G - значение канала зеленого
    /// @param B - значение канала синего
    /// @param A - значение канала прозрачности
    void fillRegion(uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, uint8_t R, uint8_t G, uint8_t B, uint8_t A);

    /// Масштабирование растрового изображения
    /// @param new_width - ширина, до которой нужно произвести масштабирование
    /// @param new_height - высота, до которой нужно произвести масштабирование
    void scale(int32_t new_width, int32_t new_height);

    /// Получение ширины растрового изображения
    /// @return - текущая ширина изображения
    int32_t getWidth() const;

    /// Получение высоты растрового изображения
    /// @return - текущая высота изображения
    int32_t getHeight() const;

    int32_t getImageSize() const;

    int32_t getBitCount() const;

    int32_t getOffsetData() const;

    int32_t getDataSizeBit() const;

    int32_t getDataSizeByte() const;

    std::vector<RGBColor> getPixelsRGB();

    void printImage(std::vector<RGBColor>) const;



protected:
#pragma pack(push, 1)
    struct FileHeader {
        /// Отметка для отличия формата от других (сигнатура формата). Может содержать единственное значение 0x4D42
        uint16_t    file_type      { 0x4D42 };

        /// Размер файла в байтах
        uint32_t    file_size      { 0 };

        /// Зарезервированное поле. Всегда должно содержать ноль
        uint16_t    reserved1      { 0 };

        /// Зарезервированное поле. Всегда должно содержать ноль
        uint16_t    reserved2      { 0 };

        /// Положение пиксельных данных относительно начала данной структуры
        uint32_t    offset_data    { 0 };
    };
#pragma pack(pop)

    struct InfoHeader {
        /// Размер данной структуры в байтах, указывающий также на версию структуры
        uint32_t    size                { 0 };

        /// Ширина растрового изображения в пикселях
        int32_t     width               { 0 };

        /// Высота растрового изображения в пикселях
        int32_t     height              { 0 };

        /// Количество цветовых плоскостей. Всегда должно быть равно единице
        uint16_t    planes              { 1 };

        /// Количество бит на пиксель
        uint16_t    bit_count           { 0 };

        /// Способ хранения пикселей
        uint32_t    compression         { 0 };

        /// Размер пиксельных данных в байтах
        uint32_t    size_image          { 0 };

        /// Количество пикселей на метр по горизонтали
        int32_t     x_pixels_per_meter  { 0 };

        /// Количество пикселей на метр по вертикали
        int32_t     y_pixels_per_meter  { 0 };

        /// Количество цветов в цветовой палитр
        uint32_t    colors_used         { 0 };

        /// Цвета, используемые растровым изображением
        uint32_t    colors_important    { 0 };
    };

    struct ColorHeader {
        /// Битовая маска для канала красного
        uint32_t    red_mask            { 0x00ff0000 };

        /// Битовая маска для канала зеленого
        uint32_t    green_mask          { 0x0000ff00 };

        /// Битовая маска для канала синего
        uint32_t    blue_mask           { 0x000000ff };

        /// Битовая маска для альфа-канала
        uint32_t    alpha_mask          { 0xff000000 };

        /// Тип цветового пространства. По-умолчанию sRGB (0x73524742)
        uint32_t    color_space_type    { 0x73524742 };

        /// Неиспользуемые данные для цветового пространства sRGB
        uint32_t    unused[16]          { 0 };
    };


    /// Заголовочная структура текущего растрового изображения
    FileHeader              m_file_header;

    /// Информационная структура текущего растрового изображения
    InfoHeader              m_info_header;

    /// Цветовая структура текущего растрового изображения
    ColorHeader             m_color_header;

    /// Хранилище для информации о пикселях
    std::vector<uint8_t>    m_data;

    /// Количество значимых байт
    uint32_t                m_row_stride;

    /// Проверка формата цвета на соответствие форматам цветов
    /// @param color_header - ColorHeader с заданными битовыми масками и типом цветового пространства
    void        _checkColorHeader(ColorHeader & color_header);

    /// Выравнивание длины строки
    /// @param align_stride - коэффициент выравнивания
    /// @return - длина выравненной строки
    uint32_t    _makeStrideAligned(uint32_t align_stride) const;

    /// Запись заголовков на диск
    /// @param stream - поток для записи
    void        _writeHeaders(std::ofstream & stream);

    /// Запись заголовков и информации о пикселях на диск
    /// @param stream - поток для записи
    void        _writeHeadersAndData(std::ofstream & stream);
};

#endif //BMP_H
