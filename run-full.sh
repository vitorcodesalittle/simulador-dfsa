mkdir -p build
cmake -S ./simulador -B ./build
cd build; make; cd ..;
cp build/simulador ./sim
echo 'Running simulator'
./sim --out plots/out 
cd plots/
mkdir -p images
echo 'Generating scripts'
python main.py out.csv images/
cd ..
echo 'Images saved at plots/images'
