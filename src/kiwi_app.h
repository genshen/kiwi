//
// Created by genshen(genshenchu@gmail.com) on 2018-03-21.
//

#ifndef KIWI_KIWI_H
#define KIWI_KIWI_H

namespace kiwi {
    /**
     * lifecycle of kiwi:
     * beforeCreate() -> create -> onCreate() -> prepare()
     * <!-- > start()--> -> onStart() -> beforeDestroy() -> destroy -> onDestroy()
     */
    class kiwiApp {
    public:

        void run(int argc, char *argv[]);

        /**
         * exit this program before finishing running.
         * please call this function after @link#create
         * @param code  exit code.
         */
        void abort(int code);

    protected:

        virtual bool beforeCreate(int argc, char *argv[]);

        virtual void onCreate();

        virtual bool prepare();

        virtual void onStart();

        virtual void beforeDestroy();

        virtual void onFinish();

        // do not use mpi in onDestroy.
        virtual void onDestroy();

    private:
        // initial mpi env for application.
        bool create(int argc,char *argv[]);

        // start app
        void start();

        // destroy
        void destroy();
    };
}

#endif //KIWI_KIWI_H
