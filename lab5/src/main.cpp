#include "Bmp/Bmp.h"
#include "Exception/Exception.hpp"
#include "Menu/Menu.hpp"
#include <any>
#include <vector>
#include <string>

using namespace YMM;

BMP* loadData(std::string file_name) {
    BMP* img_ptr = nullptr;
    try {
        img_ptr = new BMP(file_name);
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        Exception::error(std::string(e.what()));
        return nullptr;
    }
    return img_ptr;
}

void width(std::vector<std::any> params) {
    auto* img_ptr = std::any_cast<BMP*>(params[0]);

    std::cout << "img width: " << img_ptr->getWidth() << "px" << std::endl;
}

void height(std::vector<std::any> params) {
    auto* img_ptr = std::any_cast<BMP*>(params[0]);

    std::cout << "img height: " << img_ptr->getHeight() << "px" << std::endl;
}

void dataOffset(std::vector<std::any> params) {
    auto* img_ptr = std::any_cast<BMP*>(params[0]);

    std::cout << "img data offset: " << img_ptr->getOffsetData() << " byte" << std::endl;
}

void dataSizeBit(std::vector<std::any> params) {
    auto* img_ptr = std::any_cast<BMP*>(params[0]);

    std::cout << "image size in bites: " << img_ptr->getDataSizeBit() << " bit" << std::endl;
}

void dataSizeByte(std::vector<std::any> params) {
    auto* img_ptr = std::any_cast<BMP*>(params[0]);

    std::cout << "image size in bytes: " << img_ptr->getDataSizeByte() << " byte" << std::endl;
}

void allInfo(std::vector<std::any> params) {
    auto* img_ptr = std::any_cast<BMP*>(params[0]);
    
    height(params);
    width(params);
    dataOffset(params);
    dataSizeBit(params);
    dataSizeByte(params);
}

void printColors(std::vector<std::any> params) {
    auto* img_ptr = std::any_cast<BMP*>(params[0]);

    // img_ptr->getSimpleColor(img_ptr->getPixels()[0]);
    // std::cout << img_ptr->getPixelsRGB()[6] << std::endl;
    std::vector<BMP::RGBColor> rgb_pixels = img_ptr->getPixelsRGB();
    std::cout << "R:" << rgb_pixels[0].R << std::endl;
    std::cout << "G:" << rgb_pixels[0].G << std::endl;
    std::cout << "B:" << rgb_pixels[9].B << std::endl;
}

void printImage(std::vector<std::any> params) {
    auto* img_ptr = std::any_cast<BMP*>(params[0]);

    img_ptr->printImage(img_ptr->getPixelsRGB());

}

std::string YMM::Exception::log_file_name = "log.log";

int main(int argc, char *argv[]) {
    using namespace YMM;

    // read args
    std::string load_data_file = "img1_small.bmp";
    std::string log_file = "log.log";
    if (argc >= 2) {
        load_data_file = argv[1];
        log_file = argv[2];
    }

    Exception::setLogFileName(log_file);

    // data
    BMP* img_ptr = nullptr;
    img_ptr = loadData(load_data_file);
    if (!img_ptr) return -1;

    std::vector<std::any> params{
        img_ptr
    };

    Menu menu = Menu("Main", std::vector<Menu>{
                         Menu("Image width", width),
                         Menu("Image height", height),
                         Menu("Image data offset", dataOffset),
                         Menu("Image size in bites", dataSizeBit),
                         Menu("Image size in bytes", dataSizeByte),
                         Menu("Image info", allInfo),
                         Menu("Image print color", printColors),
                         Menu("Print image", printImage),
                         }, params);

    menu.run();

    return 0;
}
