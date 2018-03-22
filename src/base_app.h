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
    class baseApp {
    public:

        void run(int argc, char *argv[]);

    protected:

        bool beforeCreate();

        void onCreate();

        bool prepare();

        void onStart();

        void beforeDestroy();

        void onFinish();

        void onDestroy();

    private:
        // initial mpi env for application.
        bool create(int argc, char *argv[]);

        // start app
        void start();

        // destroy
        void destroy();
    };
}

#endif //KIWI_KIWI_H
