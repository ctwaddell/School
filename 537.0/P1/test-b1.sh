bin_name=wordle
cmd_opt="/non-existent-file random_string"
expected_stdout="wordle: cannot open file"
expected_return_code=1

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
