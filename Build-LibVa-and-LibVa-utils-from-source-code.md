# Libva
Libva is an implementation for VA-API. You can download and install it by below commands.
```bash
$ git clone https://github.com/intel/libva.git
$ ./autogen.sh --prefix=/usr --libdir=/usr/lib/x86_64-linux-gnu
$ make -j8
$ make install
```
Libva will be installed to /usr/lib/x86_64-linux-gnu/.

# Libva utils
libva-utils is a collection of utilities and examples to exercise VA-API in accordance with the libva project. --enable-tests (default = no) provides a suite of unit-tests based on Google Test Framework.
You can download it by below command.
```bash
$ git clone https://github.com/intel/libva-utils.git
```