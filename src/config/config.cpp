//
// Created by genshen(genshenchu@gmail.com) on 2018-03-21.
//

#include <fstream>
#include <toml.hpp>
#include "config.h"
#include "../utils/bundle.h"
#include "../utils/mpi_utils.h"

namespace kiwi {
    config *config::pConfigInstance = nullptr;

    config::config() : hasError(false) {}

    // a simple single mode example.
//    config *config::newInstance() {
//        if (pConfigInstance == nullptr) {
//            pConfigInstance = new config();
//        }
//        return pConfigInstance; // make sure there is a configure instance.
//    }
//
//    config *config::newInstance(const std::string &configureFilePath) {
//        if (pConfigInstance == nullptr) {
//            pConfigInstance = new config();
//            resolve(configureFilePath);
//        }
//        return pConfigInstance;
//    }

    void config::resolve(const std::string &configureFilePath) {
        std::ifstream ifs(configureFilePath);
        if (!ifs.good()) {
            setError("can not access the configure file");
            return;
        }
        auto conf = cpptoml::parse_file(configureFilePath); // todo exception
        resolveConfig(conf);
    }

    void config::setError(const std::string &msg) {
        errorMessage = msg;
        hasError = true;
    }

    void config::sync() {
        Bundle bundle = Bundle();
        bundle.newPackBuffer(1024);
        if (mpiUtils::ownRank == MASTER_PROCESSOR) { // pack data.
            putConfigData(bundle);
        }

        MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
                  MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

        if (mpiUtils::ownRank != MASTER_PROCESSOR) { // unpack data.
            getConfigData(bundle);
        }
        bundle.releasePackBuffer(); // release memory after usage.
    }

}
