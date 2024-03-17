rm -r ./idz1_7/cmake-build-debug

if ! cmake -S ./idz1_7 -B ./idz1_7/cmake-build-debug; then
    echo cmake initialize error
fi
if ! cmake --build ./idz1_7/cmake-build-debug --target idz1_7; then
    echo cmake build error
fi

echo "-------------------------------------------------------------------------"
./idz1_7/cmake-build-debug/idz1_7 -i case1i.txt -o ./idz1_7/case1o.txt
echo "-------------------------------------------------------------------------"
./idz1_7/cmake-build-debug/idz1_7 -i case2i.txt -o ./idz1_7/case2o.txt
echo "-------------------------------------------------------------------------"
./idz1_7/cmake-build-debug/idz1_7 -i case3i.txt -o ./idz1_7/case3o.txt
echo "-------------------------------------------------------------------------"
./idz1_7/cmake-build-debug/idz1_7 -i case4i.txt -o ./idz1_7/case4o.txt
echo "-------------------------------------------------------------------------"
./idz1_7/cmake-build-debug/idz1_7 -i case5i.txt -o ./idz1_7/case5o.txt
echo "-------------------------------------------------------------------------"
./idz1_7/cmake-build-debug/idz1_7
echo "-------------------------------------------------------------------------"

rm -r ./idz1_7/cmake-build-debug
