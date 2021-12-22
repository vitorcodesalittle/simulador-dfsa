mkdir -p build
cmake -S ./simulador -B ./build
cd build; make; cd ..;
cp build/simulador ./sim
echo 'Running simulator'
./sim --out plots/out --repetitions 2000 --initial-frame 128 --estimators lb,shoute,eom-lee,iv2
cd plots/
mkdir -p images
echo 'Generating plots'
python main.py out.csv images/
cd ..
./sim --out plots/out-po2-frames --repetitions 2000  --no-po2 --initial-frame 128 --estimators lb,shoute,eom-lee,iv2
cd plots/
mkdir -p images-po2
python main.py out-po2-frames.csv images-po2/
cd ..
echo 'Images saved at plots/images'
