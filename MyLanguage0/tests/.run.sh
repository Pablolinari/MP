touch tests//.timeout
CMD="   /home/pablo/Escritorio/MP/UGRMPBase/NetBeansProjects/MyLanguage0/dist/Debug/GNU-Linux/mylanguage0  < data/SimpleText.txt 1> tests//.out4 2>&1"
eval $CMD
rm tests//.timeout
