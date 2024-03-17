rm -r ./idz1_5/cmake-build-debug

if ! cmake -S ./idz1_5 -B ./idz1_5/cmake-build-debug; then
    echo cmake initialize error
fi
if ! cmake --build ./idz1_5/cmake-build-debug --target idz1_5; then
    echo cmake build error
fi

echo "-------------------------------------------------------------------------"
./idz1_5/cmake-build-debug/idz1_5 -i case1i.txt -o ./idz1_5/case1o.txt
echo "-------------------------------------------------------------------------"
./idz1_5/cmake-build-debug/idz1_5 -i case2i.txt -o ./idz1_5/case2o.txt
echo "-------------------------------------------------------------------------"
./idz1_5/cmake-build-debug/idz1_5 -i case3i.txt -o ./idz1_5/case3o.txt
echo "-------------------------------------------------------------------------"
./idz1_5/cmake-build-debug/idz1_5 -i case4i.txt -o ./idz1_5/case4o.txt
echo "-------------------------------------------------------------------------"
./idz1_5/cmake-build-debug/idz1_5 -i case5i.txt -o ./idz1_5/case5o.txt
echo "-------------------------------------------------------------------------"
./idz1_5/cmake-build-debug/idz1_5
echo "-------------------------------------------------------------------------"

rm -r ./idz1_5/cmake-build-debug
