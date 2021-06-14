RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
echo -e "${BLUE}\n#########################################"
echo -e "~~~~~~~~~~~~~~~~~ Tests ~~~~~~~~~~~~~~~~~"
echo -e "#########################################\n${NC}"

for dTest in ./test/*; do
    #OPEN FILES
    expected=$(cat ./expected/${dTest/test/}/__stdout__)
    expected_return=$(cat ./expected/${dTest/test/}/__return_code__)

    echo $dTest
    echo

    #RUN VALGRIND
    # valgrind $dTest/cmd > ${dTest/test/valgrind}
    # val_return=$?
    uno=1

    valgrind --tool=memcheck --leak-check=full --leak-resolution=med --show-reachable=yes --trace-children=yes --track-fds=yes --track-origins=no --time-stamp=yes --num-callers=20 --error-exitcode=42  --log-file=./valgrind/${dTest/test/} $dTest/cmd > ${dTest/test/output}
    val_return=$?
    cuarentaydos=42

    # Diff results
    diff --color ${dTest/test/output} ./expected/${dTest/test/}/__stdout__
    dif_return=$?
    if [ $dif_return == $uno ]
    then
        printf "${RED} FAILED: Differences in output ${NC}"
    else
        printf "${GREEN} diff OK ${NC}"
    fi
    echo

    # Return results
    if [ $val_return != $cuarentaydos ]
    then
        printf "${RED} FAILED: Bad return value ${NC}"
    else
        printf "${GREEN} return OK ${NC}"
    fi
    echo
    echo -e "\n-------------------------------------\n" 
done
