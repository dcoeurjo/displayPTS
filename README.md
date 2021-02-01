# displayPTS
![Linux/Mac/Windows build](https://github.com/dcoeurjo/displayPTS/workflows/Linux/Mac/Windows%20build/badge.svg)

`displayPTS` is a simple CLI tool to visualize tabulated ASCII
pointsets with some quantities attached to the samples (scalars or
vectors) using the excellent [polyscope](https://polyscope.run) (actually, just a few
lines of code around [polyscope](https://polyscope.run) but pretty
handy tool at the end).

For instance, if your pointset is an ASCII file `data.pts`:
```
x y z scalar1 scalar2 vector1x vector1y vector1z scalar3 scalar4...
{one line per point}
```

You can visualize the point set using:

```
./diplayPTS  -i data.pts --vectorCols 5 10
```
Each scalar column will be considered as a `ScalarQuantity` in
polyscope. `--vectorCols 5` means that columns (5,6,7) and (10,11,12)
will define  vector quantities attached to samples.

Note that  you can process several pointsets to compare them:
```
./diplayPTS  -i data1.pts data2.pts --vectorCols 5 10
```

(`./displayPTS -h` for the parameters)

![](screenshot.png)


# Building

* Get the code (and its submodules):
```
git clone --recursive https://github.com/dcoeurjo/displayPTS.git
```

* Generate the project (cmake) and build the code. For instance:
```
cd displayPTS
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

# Author

[David Coeurjolly](https://perso.liris.cnrs.fr/david.coeurjolly), CNRS
