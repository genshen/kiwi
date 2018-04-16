//
// Created by genshen(genshenchu@gmail.com) on 2018-03-21.
//

#ifndef KIWI_KIWI_APP_H
#define KIWI_KIWI_APP_H

#include "utils/mpi_utils.h"

namespace kiwi {
    /**
     * lifecycle of kiwi:
     * beforeCreate() -> create -> onCreate() -> prepare()
     * <!-- > start()--> -> onStart() -> beforeDestroy() -> destroy -> onDestroy()
     */
    class kiwiApp {
    public:

        /**
         * set @var _mpi_thread_type for MPI thread support.
         * This function must be called before function create.(@see implement of function run)
         *
         * @param type predefined variable in mpi.h, can be:
         * MPI_THREAD_SINGLE, MPI_THREAD_FUNNELED, MPI_THREAD_SERIALIZED or MPI_THREAD_MULTIPLE.
         */
        void setMPIThreadSupport(short type); // todo runtime exception.

        void run(int argc, char *argv[]);

        /**
         * exit this program before finishing running.
         * please call this function after @link#create
         * @param code  exit code.
         */
        void abort(int code);

    protected:

        virtual bool beforeCreate(int argc, char *argv[]);

        virtual void onCreate() {};

        virtual bool prepare();

        virtual void onStart() {};

        virtual void beforeDestroy() {};

        virtual void onFinish() {};

        // do not use mpi in onDestroy.
        virtual void onDestroy() {};

    private:
        /**
         * value of _mpi_thread_type can be below values, which is predefined in mpi.h
         * MPI_THREAD_SINGLE: Only one thread
         * MPI_THREAD_FUNNELED: Only main thread will make MPI calls
         * MPI_THREAD_SERIALIZED: Only one MPI call at time
         * MPI_THREAD_MULTIPLE: Multiple threads with multiple calls
         */
        short _mpi_thread_type = MPI_THREAD_SINGLE;

        // Initialize mpi env for application.
        bool create(int argc, char *argv[]);

        // start app
        void start();

        // destroy
        void destroy();
    };
}

#endif //KIWI_KIWI_APP_H
