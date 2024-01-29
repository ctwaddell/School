bin_name=my-look
cmd_opt="-V -h -f file.txt"
expected_stdout="my-look from CS537 Summer 2022"
expected_return_code=0

stdout=$(./$bin_name $cmd_opt)
ret_code=$?
if [ "$expected_stdout" = "$stdout" ]; then
    if [ $ret_code -ne $expected_return_code ]; then
        echo return code mismatch $ret_code -ne $expected_return_code
    else
        echo test passed $bin_name $cmd_opt "->" ret $ret_code
    fi
else
    echo test failed $bin_name $cmd_opt "->" has stdout: $stdout " | "expected: $expected_stdout
fi
