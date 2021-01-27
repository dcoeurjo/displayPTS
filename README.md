# displayPTS

`displayPTS` is a simple CLI tool to visualize tabulated ASCII
pointsets with some quantities attached to the samples (scalars or
vectors) using [polyscope](https://polyscope.run) (actually, just a few
lines of code around [polyscope](https://polyscope.run) but pretty
handy tool).

For instance, if your pointset is an ascii file `data.pts`:
```
x y z scalar1 scalar2 vector1x vector1y vector1z scalar3 scalar4...
{one line per point}
```

You can visualize the point set using:

```
./diplayPTS  -i data.pts --vectorCols 5
```
Each scalar columns will be considered as a `ScalarQuantity` in
polyscope. `--vectorCols 5` means that columns 5 6 and 7 defines a vector quantity.

Note that  you can display multiple files:
```
./diplayPTS  -i data1.pts data2.pts --vectorCols 5
```

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

# Authors

[David Coeurjolly](https://perso.liris.cnrs.fr/david.coeurjolly), CNRS
