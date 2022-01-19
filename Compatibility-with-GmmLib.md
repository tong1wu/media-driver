- There was a known incompatible issue in [GmmLib](https://github.com/intel/gmmlib) before first Gmmlib tag intel-gmmlib-18.3.pre1 which introduced from [gmmlib/d6c3b56](https://github.com/intel/gmmlib/commit/d6c3b56745798bdd0c7e4920ebb5b4192225c17b) and reverted in [gmmlib/f7b5da5](https://github.com/intel/gmmlib/commit/f7b5da59be9fcb1edc57394703e96ebaf59a39ff).
It's NOT suggested to use the GmmLib revision between this range.

- [GmmLib API broken](https://github.com/intel/gmmlib/issues/92) between 21.x and 22.x. If your GmmLib is <=21.x serial(except intel-gmmlib-21.3.4), it's compatible with media-driver <=21.x serial but incompatible with media-driver >=22.x serial. If your GmmLib is >=22.x serial, it's necessary to upgrade media-driver >=22.x serial.

