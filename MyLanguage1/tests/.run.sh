touch tests//.timeout
CMD="valgrind --leak-check=full /home/pablo/Escritorio/MP/UGRMPBase/NetBeansProjects/MyLanguage1/dist/Debug/GNU-Linux/mylanguage1  < data/SimpleTextbigrams.txt 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
