rm -r ./idz1_6/cmake-build-debug

if ! cmake -S ./idz1_6 -B ./idz1_6/cmake-build-debug; then
    echo cmake initialize error
fi
if ! cmake --build ./idz1_6/cmake-build-debug --target idz1_6; then
    echo cmake build error
fi

echo "-------------------------------------------------------------------------"
./idz1_6/cmake-build-debug/idz1_6 -i case1i.txt -o ./idz1_6/case1o.txt
echo "-------------------------------------------------------------------------"
./idz1_6/cmake-build-debug/idz1_6 -i case2i.txt -o ./idz1_6/case2o.txt
echo "-------------------------------------------------------------------------"
./idz1_6/cmake-build-debug/idz1_6 -i case3i.txt -o ./idz1_6/case3o.txt
echo "-------------------------------------------------------------------------"
./idz1_6/cmake-build-debug/idz1_6 -i case4i.txt -o ./idz1_6/case4o.txt
echo "-------------------------------------------------------------------------"
./idz1_6/cmake-build-debug/idz1_6 -i case5i.txt -o ./idz1_6/case5o.txt
echo "-------------------------------------------------------------------------"
./idz1_6/cmake-build-debug/idz1_6
echo "-------------------------------------------------------------------------"

rm -r ./idz1_6/cmake-build-debug
