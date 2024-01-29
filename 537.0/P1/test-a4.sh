bin_name=my-look
expected_return_code=0
expected_out=3
out1=$(cat /usr/share/dict/words | ./$bin_name gnus)
ret_code=$?
out=$(echo "$out1" | wc -l)
if [ "$out" = "$expected_out" ]; then
    if [ $ret_code -ne $expected_return_code ]; then
        echo return code mismatch $ret_code -ne $expected_return_code
    else
        echo test4 passed
    fi
else
    echo test4 failed. matched $out lines instead of $expected_out
fi
