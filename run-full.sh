mkdir -p build
cmake -S ./simulador -B ./build
cd build; make; cd ..;
cp build/simulador ./sim
echo 'Running simulator'
./sim --out plots/out --repetitions 1000 
./sim --out plots/out-po2-frames --repetitions 1000  --no-po2
cd plots/
mkdir -p images
echo 'Generating plots'
python main.py out.csv images/
mkdir -p images-po2
python main.py out-po2-frames.csv images-po2/
cd ..
echo 'Images saved at plots/images'
