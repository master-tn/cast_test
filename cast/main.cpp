#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <random>
#include <algorithm>
#include "Object.h"
#include "Box.h"
#include "Triangle.h"
#include "IWrite.h"

void dynamic_cast_test()
{
    std::cout << "dynamic_cast_test" <<std::endl;
    
    const int num = 5000;
    std::vector<std::shared_ptr<Object>> objectList;
    objectList.reserve(num);
    
    for (int i = 0; i < num; ++i)
    {
        objectList.emplace_back(std::make_shared<Box>(i));
    }
    
    //計測
    double static_result = 0;
    double dynamic_result = 0;
    {
        auto start = std::chrono::system_clock::now(); // 計測開始時間
        const size_t size = objectList.size();
        for (size_t i = 0; i < size; ++i)
        {
            auto box = std::static_pointer_cast<Box>(objectList[i]);
            box->print();
        }
        auto end = std::chrono::system_clock::now();  // 計測終了時間
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        static_result = elapsed;
    }
    
    std::cout << "next" << std::endl;
    
    //計測
    {
        auto start = std::chrono::system_clock::now(); // 計測開始時間
        const size_t size = objectList.size();
        for (size_t i = 0; i < size; ++i)
        {
            auto box = std::dynamic_pointer_cast<Box>(objectList[i]);
            box->print();
        }
        auto end = std::chrono::system_clock::now();  // 計測終了時間
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        dynamic_result = elapsed;
    }
    
    std::cout << "static elapsed=" << static_result << "msec" << std::endl;
    std::cout << "dynamic elapsed=" << dynamic_result << "msec" << std::endl;
}

void type_check_test()
{
    std::cout << "type_check_test" << std::endl;
    
    const int num = 10000;
    std::vector<std::shared_ptr<Object>> objectList;
    objectList.reserve(num);
    
    for (int i = 0; i < num / 2; ++i)
    {
        objectList.emplace_back(std::make_shared<Box>(i));
    }
    for (int i = num / 2; i < num; ++i)
    {
        objectList.emplace_back(std::make_shared<Triangle>(i));
    }
    
    //ランダムシャッフル
    std::mt19937_64 get_rand_mt;
    std::shuffle(objectList.begin(), objectList.end(), get_rand_mt);
    
    double static_result = 0;
    double dynamic_result = 0;
    //型をチェックしながらstatic_pointer_castして出力
    {
        auto start = std::chrono::system_clock::now(); // 計測開始時間
        const size_t size = objectList.size();
        for (size_t i = 0; i < size; ++i)
        {
            auto spObject = objectList[i];
            switch(spObject->getType())
            {
                case Type::Box:
                {
                    auto box = std::static_pointer_cast<Box>(spObject);
                    box->print();
                }
                    break;
                    
                case Type::Triangle:
                {
                    auto tri = std::static_pointer_cast<Triangle>(spObject);
                    tri->put();
                }
                    break;
                default:
                    break;
            }
        }
        auto end = std::chrono::system_clock::now();  // 計測終了時間
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        static_result = elapsed;
    }
    
    std::cout << "next" << std::endl;
    
    //dynamic_pointer_castで
    {
        auto start = std::chrono::system_clock::now(); // 計測開始時間
        const size_t size = objectList.size();
        for (size_t i = 0; i < size; ++i)
        {
            auto spObject = objectList[i];
            if (auto spBox = std::dynamic_pointer_cast<Box>(spObject))
            {
                spBox->print();
            }
            else if(auto spTri = std::dynamic_pointer_cast<Triangle>(spObject))
            {
                spTri->put();
            }
        }
        auto end = std::chrono::system_clock::now();  // 計測終了時間
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        dynamic_result = elapsed;
    }
    
    std::cout << "next" << std::endl;
    
    //共通インターフェースでのコールで検証
    std::vector<std::shared_ptr<IWrite>> iList;
    iList.reserve(num);
    
    for (int i = 0; i < num / 2; ++i)
    {
        iList.emplace_back(std::make_shared<Box>(i));
    }
    for (int i = num / 2; i < num; ++i)
    {
        iList.emplace_back(std::make_shared<Triangle>(i));
    }
    
    //ランダムシャッフル
    std::shuffle(iList.begin(), iList.end(), get_rand_mt);
    double interface_result = 0;
    {
        auto start = std::chrono::system_clock::now(); // 計測開始時間
        const size_t size = iList.size();
        for (size_t i = 0; i < size; ++i)
        {
            auto sp = iList[i];
            sp->write();
        }
        auto end = std::chrono::system_clock::now();  // 計測終了時間
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        interface_result = elapsed;
    }
    
    std::cout << "static elapsed=" << static_result << "msec" << std::endl;
    std::cout << "dynamic elapsed=" << dynamic_result << "msec" << std::endl;
    std::cout << "interface elapsed=" << interface_result << "msec" << std::endl;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    dynamic_cast_test();
    
    type_check_test();
    
    return 0;
}
