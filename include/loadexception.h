#include "commonheaders.h"
/**
 * loadException类。
 * 
 * 该类继承自std::exception，用于处理加载异常。
 */
class loadException : public std::exception {
public:
    /**
     * loadException类的构造函数。
     * 
     * @param message 异常消息。
     */
    loadException(const std::string& file,const std::string& filetype) : file(file) {}
    
    /**
     * what()函数，用于获取异常消息。
     * 
     * 该函数返回一个指向异常消息的常量字符指针。
     * 
     * @return 指向异常消息的常量字符指针。
     */
    const char* what() const noexcept override {
        message = "Could not load \"" + filetype + "\" file: \"" + file +"\"";
        return message.c_str();
    }
private:
    std::string file;
    std::string filetype;
    mutable std::string message;
};