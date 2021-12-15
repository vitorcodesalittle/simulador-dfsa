mkdir -q build
cmake -S ./simulador -B ./build
cd build; make; cd ..;
cp build/simulador ./sim
sim --out plots/out 
cd plots/
mkdir images
python main.py out.csv images/
cd ..
echo 'Images saved at plots/images'
