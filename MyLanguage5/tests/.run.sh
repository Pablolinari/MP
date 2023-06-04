touch tests//.timeout
CMD="valgrind --leak-check=full /home/arnold/Escritorio/UGRMPBase/NetBeansProjects/MyLanguage5/./dist/JOIN/GNU-Linux/JOIN  JOIN -O tests/output/30bigrams.bgr ../Books/30bigrams.bgr 1> tests//.out1 2>&1"
eval $CMD
rm tests//.timeout
