#!/usr/bin/env ruby

$test_bin = ARGV[0]
$failures = 0
$tests_finished = 0

if $test_bin.nil?
  raise "Usage: test.rb $BINARY"
end

def test(prg, corpus, expected_code)
  read_pipe, write_pipe = IO.pipe()
  read_pipe2, write_pipe2 = IO.pipe()

  child_pid = fork() do
    write_pipe.close()
    read_pipe2.close()

    $stdin.reopen read_pipe
    $stdout.reopen write_pipe2
    exec $test_bin, prg
  end
  read_pipe.close()
  write_pipe2.close()

  write_pipe.write corpus
  write_pipe.close()

  # TODO consume read_pipe2 completely before wait-ing
  Process.wait child_pid
  res = $?

  code = res.exitstatus
  $tests_finished += 1
  if code != expected_code
    printf "\"#{prg}\" failed with #{res}\n"
    $failures += 1
  end

  printf "\rRan #{$tests_finished} tests."
end

test '.*4\.2bsd$', "# Title\nfrom 4.2bsd\n", 0
test 'b.d',                 "from 4.2bsd\n", 0
test '42bsd',               "from 4.2bsd\n", 1
test '4',          "         from 4.2bsd\n", 0
# + not implemented
test '.+', "      from 4.2bsd\n", 1

printf "\n"

if $failures != 0
  $stderr.printf "#{$failures} failures\n"
  exit 1
else
  exit 0
end
