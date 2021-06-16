//
// Created by genshen(genshenchu@gmail.com) on 2018-03-21.
//

#ifndef KIWI_CONFIG_H
#define KIWI_CONFIG_H

#include <memory>
#include <string>
#include "../utils/bundle.h"

namespace kiwi {

    /**
     * config component.
     * new config -> resolve() -> resolveConfig -> sync()
     */
    class config {
    public:
        /**
         * Error flag while resolving toml config file.
         */
        bool hasError;

        /**
         * The error message while resolving config.
         */
        std::string errorMessage;

        // make a new instance without resolving config file.
//        config *newInstance();

//        config *newInstance(const std::string &configureFilePath);

        // sync config data to all processors in MPI_COMM_WORLD
        void sync(const unsigned int buffer_size = 1024);

        void setError(const std::string &msg);

    protected:

        config();

        // you can override the method to pack data into buffer.
        virtual void putConfigData(Bundle &bundle) = 0;

        // you can override the method to unpack data into buffer.
        virtual void getConfigData(kiwi::Bundle &bundle) = 0;

    };

}

#endif //KIWI_CONFIG_H
