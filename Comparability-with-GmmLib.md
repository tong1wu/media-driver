There was a commit https://github.com/intel/gmmlib/commit/d6c3b56745798bdd0c7e4920ebb5b4192225c17b in GmmLib (https://github.com/intel/gmmlib) caused inter-operation problem between GmmLib and Media, which was reverted at https://github.com/intel/gmmlib/commit/f7b5da59be9fcb1edc57394703e96ebaf59a39ff.
Please don't use the GmmLib between this range.
