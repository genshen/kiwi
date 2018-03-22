//
// Created by genshen(genshenchu@gmail.com) on 2018-03-21.
//

#ifndef KIWI_CONFIG_H
#define KIWI_CONFIG_H


#include <string>
#include "../utils/bundle.h"

namespace kiwi {

    class config {
    public:
        bool hasError = false;
        std::string errorMessage;

        // make a new instance without resolving config file.
        config *newInstance();

        config *newInstance(const std::string &configureFilePath);

        void sync();

        void setError(const std::string &msg);

    protected:

        // resolve config file.
        void resolve(const std::string &basic_string);

        virtual
        void resolveConfig(std::shared_ptr<cpptoml::table> table) = 0;

        virtual // you can override the method to pack data into buffer.
        void putConfigData(Bundle &Bundle)= 0;

        virtual // you can override the method to unpack data into buffer.
        void getConfigData(kiwi::Bundle &Bundle)= 0;

    protected:
        static config *pConfigInstance;

        config();
    };

}

#endif //KIWI_CONFIG_H
