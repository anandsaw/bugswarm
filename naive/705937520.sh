#!/bin/bash
export TRAVIS_ROOT=/
export TRAVIS_HOME=${HOME}
export TRAVIS_BUILD_DIR=${HOME}/build
export TRAVIS_INTERNAL_RUBY_REGEX=\^ruby-\(2\\.\[0-4\]\\.\[0-9\]\|1\\.9\\.3\)
export TRAVIS_APP_HOST=
export TRAVIS_APT_PROXY=
travis_preamble() {
  if [[ -s "${TRAVIS_ROOT}/etc/profile" ]]; then
    # shellcheck source=/dev/null
    source "${TRAVIS_ROOT}/etc/profile"
  fi

  if [[ -s "${TRAVIS_HOME}/.bash_profile" ]]; then
    # shellcheck source=/dev/null
    source "${TRAVIS_HOME}/.bash_profile"
  fi

  mkdir -p "${TRAVIS_HOME}/.travis"
  echo "source ${TRAVIS_HOME}/.travis/job_stages" >>"${TRAVIS_HOME}/.bashrc"

  mkdir -p "${TRAVIS_BUILD_DIR}"
  cd "${TRAVIS_BUILD_DIR}" || exit 86
}

travis_preamble
echo \#\ travis_.\+\ functions:'
'travis_apt_get_update\(\)\ \{'
'\ \ if\ \!\ command\ -v\ apt-get\ \&\>/dev/null\;\ then'
'\ \ \ \ return'
'\ \ fi'
''
'\ \ local\ logdest\=\"\$\{TRAVIS_HOME\}/apt-get-update.log\"'
'\ \ local\ opts\=\'-yq\''
'\ \ if\ \[\[\ \"\$\{1\}\"\ \=\=\ debug\ \]\]\;\ then'
'\ \ \ \ opts\=\'\''
'\ \ \ \ logdest\=\'/dev/stderr\''
'\ \ fi'
''
'\ \ sudo\ rm\ -rf\ \"\$\{TRAVIS_ROOT\}/var/lib/apt/lists/\"\*'
'\ \ sudo\ apt-get\ update\ \$\{opts\}\ 2\>\&1\ \|\ tee\ -a\ \"\$\{logdest\}\"\ \&\>/dev/null'
'\}'
''
'travis_assert\(\)\ \{'
'\ \ local\ result\=\"\$\{1:-\$\{\?\}\}\"'
'\ \ if\ \[\[\ \"\$\{result\}\"\ -ne\ 0\ \]\]\;\ then'
'\ \ \ \ printf\ \"\$\{ANSI_RED\}The\ command\ \\\"\%s\\\"\ failed\ and\ exited\ with\ \$\{result\}\ during\ \%s.\$\{ANSI_RESET\}\\\\n\"\ \"\$\{TRAVIS_CMD\}\"\ \"\$\{TRAVIS_STAGE\}\"'
'\ \ \ \ printf\ \"\\\\nYour\ build\ has\ been\ stopped.\\\\n\"'
'\ \ \ \ travis_terminate\ 2'
'\ \ fi'
'\}'
''
'travis_bash_qsort_numeric\(\)\ \{'
'\ \ local\ pivot\ i\ smaller\=\(\)\ larger\=\(\)'
'\ \ travis_bash_qsort_numeric_ret\=\(\)'
'\ \ \(\(\$\#\ \=\=\ 0\)\)\ \&\&\ return\ 0'
'\ \ pivot\=\"\$\{1\}\"'
'\ \ shift'
'\ \ for\ i\;\ do'
'\ \ \ \ if\ \[\[\ \"\$\{i\%\%_\*\}\"\ -lt\ \"\$\{pivot\%\%_\*\}\"\ \]\]\;\ then'
'\ \ \ \ \ \ smaller\+\=\(\"\$\{i\}\"\)'
'\ \ \ \ else'
'\ \ \ \ \ \ larger\+\=\(\"\$\{i\}\"\)'
'\ \ \ \ fi'
'\ \ done'
'\ \ travis_bash_qsort_numeric\ \"\$\{smaller\[@\]\}\"'
'\ \ smaller\=\(\"\$\{travis_bash_qsort_numeric_ret\[@\]\}\"\)'
'\ \ travis_bash_qsort_numeric\ \"\$\{larger\[@\]\}\"'
'\ \ larger\=\(\"\$\{travis_bash_qsort_numeric_ret\[@\]\}\"\)'
'\ \ travis_bash_qsort_numeric_ret\=\(\"\$\{smaller\[@\]\}\"\ \"\$\{pivot\}\"\ \"\$\{larger\[@\]\}\"\)'
'\}'
''
'travis_cleanup\(\)\ \{'
'\ \ if\ \[\[\ -n\ \$SSH_AGENT_PID\ \]\]\;\ then'
'\ \ \ \ kill\ \"\$SSH_AGENT_PID\"\ \&\>/dev/null'
'\ \ fi'
'\}'
''
'travis_cmd\(\)\ \{'
'\ \ local\ assert\ output\ display\ retry\ timing\ cmd\ result\ secure\ event'
''
'\ \ cmd\=\"\$\{1\}\"'
'\ \ export\ TRAVIS_CMD\=\"\$\{cmd\}\"'
'\ \ shift'
''
'\ \ while\ true\;\ do'
'\ \ \ \ case\ \"\$\{1\}\"\ in'
'\ \ \ \ --assert\)'
'\ \ \ \ \ \ assert\=true'
'\ \ \ \ \ \ shift'
'\ \ \ \ \ \ \;\;'
'\ \ \ \ --echo\)'
'\ \ \ \ \ \ output\=true'
'\ \ \ \ \ \ shift'
'\ \ \ \ \ \ \;\;'
'\ \ \ \ --display\)'
'\ \ \ \ \ \ display\=\"\$\{2\}\"'
'\ \ \ \ \ \ shift\ 2'
'\ \ \ \ \ \ \;\;'
'\ \ \ \ --retry\)'
'\ \ \ \ \ \ retry\=true'
'\ \ \ \ \ \ shift'
'\ \ \ \ \ \ \;\;'
'\ \ \ \ --timing\)'
'\ \ \ \ \ \ timing\=true'
'\ \ \ \ \ \ shift'
'\ \ \ \ \ \ \;\;'
'\ \ \ \ --event\)'
'\ \ \ \ \ \ event\=\"\$\{2\}\"'
'\ \ \ \ \ \ shift\ 2'
'\ \ \ \ \ \ \;\;'
'\ \ \ \ --secure\)'
'\ \ \ \ \ \ secure\=\"\ 2\>/dev/null\"'
'\ \ \ \ \ \ shift'
'\ \ \ \ \ \ \;\;'
'\ \ \ \ \*\)\ break\ \;\;'
'\ \ \ \ esac'
'\ \ done'
''
'\ \ if\ \[\[\ -n\ \"\$\{timing\}\"\ \]\]\;\ then'
'\ \ \ \ travis_time_start\ \"\$\{event\}\"'
'\ \ fi'
''
'\ \ if\ \[\[\ -n\ \"\$\{output\}\"\ \]\]\;\ then'
'\ \ \ \ echo\ \"\\\$\ \$\{display:-\$\{cmd\}\}\"'
'\ \ fi'
''
'\ \ if\ \[\[\ -n\ \"\$\{retry\}\"\ \]\]\;\ then'
'\ \ \ \ travis_retry\ eval\ \"\$\{cmd\}\ \$\{secure\}\"'
'\ \ \ \ result\=\"\$\{\?\}\"'
'\ \ else'
'\ \ \ \ if\ \[\[\ -n\ \"\$\{secure\}\"\ \]\]\;\ then'
'\ \ \ \ \ \ eval\ \"\$\{cmd\}\ \$\{secure\}\"\ 2\>/dev/null'
'\ \ \ \ else'
'\ \ \ \ \ \ eval\ \"\$\{cmd\}\ \$\{secure\}\"'
'\ \ \ \ fi'
'\ \ \ \ result\=\"\$\{\?\}\"'
'\ \ \ \ if\ \[\[\ -n\ \"\$\{secure\}\"\ \&\&\ \"\$\{result\}\"\ -ne\ 0\ \]\]\;\ then'
'\ \ \ \ \ \ echo\ -e\ \"\$\{ANSI_RED\}We\ were\ unable\ to\ parse\ one\ of\ your\ secure\ environment\ variables.\$\{ANSI_CLEAR\}'
'\$\{ANSI_RED\}Please\ make\ sure\ to\ escape\ special\ characters\ such\ as\ \'\ \'\ \(white\ space\)\ and\ \$\ \(dollar\ symbol\)\ with\ \\\\\ \(backslash\)\ .\$\{ANSI_CLEAR\}'
'\$\{ANSI_RED\}For\ example,\ thi\\\$isanexample\ would\ be\ typed\ as\ thi\\\\\\\$isanexample.\ See\ https://docs.travis-ci.com/user/encryption-keys.\$\{ANSI_CLEAR\}\"'
'\ \ \ \ fi'
'\ \ fi'
''
'\ \ if\ \[\[\ -n\ \"\$\{timing\}\"\ \]\]\;\ then'
'\ \ \ \ travis_time_finish\ \"\$\{event\}\"'
'\ \ fi'
''
'\ \ if\ \[\[\ -n\ \"\$\{assert\}\"\ \]\]\;\ then'
'\ \ \ \ travis_assert\ \"\$\{result\}\"'
'\ \ fi'
''
'\ \ return\ \"\$\{result\}\"'
'\}'
''
'travis_decrypt\(\)\ \{'
'\ \ echo\ \"\$\{1\}\"\ \|'
'\ \ \ \ base64\ -d\ \|'
'\ \ \ \ openssl\ rsautl\ -decrypt\ -inkey\ \"\$\{TRAVIS_HOME\}/.ssh/id_rsa.repo\"'
'\}'
''
'decrypt\(\)\ \{'
'\ \ travis_decrypt\ \"\$\{@\}\"'
'\}'
''
'travis_download\(\)\ \{'
'\ \ local\ src\=\"\$\{1\}\"'
'\ \ local\ dst\=\"\$\{2\}\"'
''
'\ \ if\ curl\ --version\ \&\>/dev/null\;\ then'
'\ \ \ \ curl\ -fsSL\ --connect-timeout\ 1\ \"\$\{src\}\"\ -o\ \"\$\{dst\}\"\ 2\>/dev/null'
'\ \ \ \ return\ \"\$\{\?\}\"'
'\ \ fi'
''
'\ \ if\ wget\ --version\ \&\>/dev/null\;\ then'
'\ \ \ \ wget\ --connect-timeout\ 1\ -q\ \"\$\{src\}\"\ -O\ \"\$\{dst\}\"\ 2\>/dev/null'
'\ \ \ \ return\ \"\$\{\?\}\"'
'\ \ fi'
''
'\ \ return\ 1'
'\}'
''
'travis_find_jdk_path\(\)\ \{'
'\ \ local\ vendor\ version\ jdkpath\ result\ jdk'
'\ \ jdk\=\"\$1\"'
'\ \ vendor\=\"\$2\"'
'\ \ version\=\"\$3\"'
'\ \ if\ \[\[\ \"\$vendor\"\ \=\=\ \"openjdk\"\ \]\]\;\ then'
'\ \ \ \ apt_glob\=\"/usr/lib/jvm/java-1.\$\{version\}.\*openjdk\*\"'
'\ \ elif\ \[\[\ \"\$vendor\"\ \=\=\ \"oracle\"\ \]\]\;\ then'
'\ \ \ \ apt_glob\=\"/usr\*/lib/jvm/java-\$\{version\}-oracle\"'
'\ \ fi'
'\ \ shopt\ -s\ nullglob'
'\ \ for\ jdkpath\ in\ /usr\*/local/lib/jvm/\"\$jdk\"\ \$apt_glob\;\ do'
'\ \ \ \ \[\[\ \!\ -d\ \"\$jdkpath\"\ \]\]\ \&\&\ continue'
'\ \ \ \ result\=\"\$jdkpath\"'
'\ \ \ \ break'
'\ \ done'
'\ \ shopt\ -u\ nullglob'
'\ \ echo\ \"\$result\"'
'\}'
''
'travis_fold\(\)\ \{'
'\ \ local\ action\=\"\$\{1\}\"'
'\ \ local\ name\=\"\$\{2\}\"'
'\ \ echo\ -en\ \"travis_fold:\$\{action\}:\$\{name\}\\\\r\$\{ANSI_CLEAR\}\"'
'\}'
''
'travis_footer\(\)\ \{'
'\ \ :\ \"\$\{TRAVIS_TEST_RESULT:\=86\}\"'
'\ \ echo\ -e\ \"\\\\nDone.\ Your\ build\ exited\ with\ \$\{TRAVIS_TEST_RESULT\}.\"'
'\ \ travis_terminate\ \"\$\{TRAVIS_TEST_RESULT\}\"'
'\}'
''
'travis_install_jdk\(\)\ \{'
'\ \ local\ url\ vendor\ version\ license\ jdk\ certlink'
'\ \ jdk\=\"\$1\"'
'\ \ vendor\=\"\$2\"'
'\ \ version\=\"\$3\"'
''
'\ \ case\ \"\$\{TRAVIS_CPU_ARCH\}\"\ in'
'\ \ \"arm64\"\ \|\ \"s390x\"\ \|\ \"ppc64le\"\)'
'\ \ \ \ travis_install_jdk_package\ \"\$version\"'
'\ \ \ \ \;\;'
'\ \ \*\)'
'\ \ \ \ travis_install_jdk_ext_provider\ \"\$jdk\"\ \"\$vendor\"\ \"\$version\"'
'\ \ \ \ \;\;'
'\ \ esac'
'\}'
''
'travis_install_jdk_ext_provider\(\)\ \{'
'\ \ local\ url\ vendor\ version\ license\ jdk\ certlink'
'\ \ jdk\=\"\$1\"'
'\ \ vendor\=\"\$2\"'
'\ \ version\=\"\$3\"'
'\ \ if\ \[\[\ \"\$vendor\"\ \=\=\ openjdk\ \]\]\;\ then'
'\ \ \ \ license\=GPL'
'\ \ elif\ \[\[\ \"\$vendor\"\ \=\=\ oracle\ \]\]\;\ then'
'\ \ \ \ license\=BCL'
'\ \ fi'
'\ \ mkdir\ -p\ \~/bin'
'\ \ url\=\"https://\$TRAVIS_APP_HOST/files/install-jdk.sh\"'
'\ \ if\ \!\ travis_download\ \"\$url\"\ \~/bin/install-jdk.sh\;\ then'
'\ \ \ \ url\=\"https://raw.githubusercontent.com/sormuras/bach/master/install-jdk.sh\"'
'\ \ \ \ travis_download\ \"\$url\"\ \~/bin/install-jdk.sh\ \|\|\ \{'
'\ \ \ \ \ \ echo\ \"\$\{ANSI_RED\}Could\ not\ acquire\ install-jdk.sh.\ Stopping\ build.\$\{ANSI_RESET\}\"\ \>/dev/stderr'
'\ \ \ \ \ \ travis_terminate\ 2'
'\ \ \ \ \}'
'\ \ fi'
'\ \ chmod\ \+x\ \~/bin/install-jdk.sh'
'\ \ travis_cmd\ \"export\ JAVA_HOME\=\~/\$jdk\"\ --echo'
'\ \ \#\ shellcheck\ disable\=SC2016'
'\ \ travis_cmd\ \'export\ PATH\=\"\$JAVA_HOME/bin:\$PATH\"\'\ --echo'
'\ \ \[\[\ \"\$TRAVIS_OS_NAME\"\ \=\=\ linux\ \&\&\ \"\$vendor\"\ \=\=\ openjdk\ \]\]\ \&\&\ certlink\=\"\ --cacerts\"'
'\ \ \#\ shellcheck\ disable\=2088'
'\ \ travis_cmd\ \"\~/bin/install-jdk.sh\ --target\ \\\"\$JAVA_HOME\\\"\ --workspace\ \\\"\$TRAVIS_HOME/.cache/install-jdk\\\"\ --feature\ \\\"\$version\\\"\ --license\ \\\"\$license\\\"\$certlink\"\ --echo\ --assert'
'\}'
''
'travis_install_jdk_package\(\)\ \{'
''
'\ \ local\ JAVA_VERSION'
'\ \ JAVA_VERSION\=\"\$1\"'
'\ \ sudo\ apt-get\ update\ -yqq'
'\ \ PACKAGE\=\"adoptopenjdk-\$\{JAVA_VERSION\}-hotspot\"'
'\ \ if\ \!\ dpkg\ -s\ \"\$PACKAGE\"\ \>/dev/null\ 2\>\&1\;\ then'
'\ \ \ \ if\ dpkg-query\ -l\ adoptopenjdk\*\ \>/dev/null\ 2\>\&1\;\ then'
'\ \ \ \ \ \ dpkg-query\ -l\ adoptopenjdk\*\ \|\ grep\ adoptopenjdk\ \|\ awk\ \'\{print\ \$2\}\'\ \|\ xargs\ sudo\ dpkg\ -P'
'\ \ \ \ fi'
'\ \ \ \ sudo\ apt-get\ -yqq\ --no-install-suggests\ --no-install-recommends\ install\ \"\$PACKAGE\"\ \|\|\ true'
'\ \ fi'
'\}'
''
'travis_internal_ruby\(\)\ \{'
'\ \ if\ \!\ type\ rvm\ \&\>/dev/null\;\ then'
'\ \ \ \ \#\ shellcheck\ source\=/dev/null'
'\ \ \ \ source\ \"\$\{TRAVIS_HOME\}/.rvm/scripts/rvm\"\ \&\>/dev/null'
'\ \ fi'
'\ \ local\ i\ selected_ruby\ rubies_array_sorted\ rubies_array_len'
'\ \ local\ rubies_array\=\(\)'
'\ \ while\ IFS\=\$\'\\n\'\ read\ -r\ line\;\ do'
'\ \ \ \ rubies_array\+\=\(\"\$\{line\}\"\)'
'\ \ done\ \<\ \<\('
'\ \ \ \ rvm\ list\ strings\ \|'
'\ \ \ \ \ \ while\ read\ -r\ v\;\ do'
'\ \ \ \ \ \ \ \ if\ \[\[\ \!\ \"\$\{v\}\"\ \=\~\ \$\{TRAVIS_INTERNAL_RUBY_REGEX\}\ \]\]\;\ then'
'\ \ \ \ \ \ \ \ \ \ continue'
'\ \ \ \ \ \ \ \ fi'
'\ \ \ \ \ \ \ \ v\=\"\$\{v//ruby-/\}\"'
'\ \ \ \ \ \ \ \ v\=\"\$\{v\%\%-\*\}\"'
'\ \ \ \ \ \ \ \ echo\ \"\$\(travis_vers2int\ \"\$\{v\}\"\)_\$\{v\}\"'
'\ \ \ \ \ \ done'
'\ \ \)'
'\ \ travis_bash_qsort_numeric\ \"\$\{rubies_array\[@\]\}\"'
'\ \ rubies_array_sorted\=\(\"\$\{travis_bash_qsort_numeric_ret\[@\]\}\"\)'
'\ \ rubies_array_len\=\"\$\{\#rubies_array_sorted\[@\]\}\"'
'\ \ if\ \(\(rubies_array_len\ \<\=\ 0\)\)\;\ then'
'\ \ \ \ echo\ \'default\''
'\ \ else'
'\ \ \ \ i\=\$\(\(rubies_array_len\ -\ 1\)\)'
'\ \ \ \ selected_ruby\=\"\$\{rubies_array_sorted\[\$\{i\}\]\}\"'
'\ \ \ \ selected_ruby\=\"\$\{selected_ruby\#\#\*_\}\"'
'\ \ \ \ echo\ \"\$\{selected_ruby:-default\}\"'
'\ \ fi'
'\}'
''
'travis_jigger\(\)\ \{'
'\ \ local\ cmd_pid\=\"\$\{1\}\"'
'\ \ shift'
'\ \ local\ timeout\=\"\$\{1\}\"'
'\ \ shift'
'\ \ local\ count\=0'
''
'\ \ echo\ -e\ \"\\\\n\"'
''
'\ \ while\ \[\[\ \"\$\{count\}\"\ -lt\ \"\$\{timeout\}\"\ \]\]\;\ do'
'\ \ \ \ count\=\"\$\(\(count\ \+\ 1\)\)\"'
'\ \ \ \ echo\ -ne\ \"Still\ running\ \(\$\{count\}\ of\ \$\{timeout\}\):\ \$\{\*\}\\\\r\"'
'\ \ \ \ sleep\ 60'
'\ \ done'
''
'\ \ echo\ -e\ \"\\\\n\$\{ANSI_RED\}Timeout\ \(\$\{timeout\}\ minutes\)\ reached.\ Terminating\ \\\"\$\{\*\}\\\"\$\{ANSI_RESET\}\\\\n\"'
'\ \ kill\ -9\ \"\$\{cmd_pid\}\"'
'\}'
''
'travis_jinfo_file\(\)\ \{'
'\ \ local\ vendor\ version'
'\ \ vendor\=\"\$1\"'
'\ \ version\=\"\$2\"'
'\ \ if\ \[\[\ \"\$vendor\"\ \=\=\ oracle\ \]\]\;\ then'
'\ \ \ \ echo\ \".java-\$\{version\}-\$\{vendor\}.jinfo\"'
'\ \ elif\ \[\[\ \"\$vendor\"\ \=\=\ openjdk\ \]\]\;\ then'
'\ \ \ \ echo\ \".java-1.\$\{version\}.\*-\$\{vendor\}-\*.jinfo\"'
'\ \ fi'
'\}'
''
'travis_nanoseconds\(\)\ \{'
'\ \ local\ cmd\=\'date\''
'\ \ local\ format\=\'\+\%s\%N\''
''
'\ \ if\ hash\ gdate\ \>/dev/null\ 2\>\&1\;\ then'
'\ \ \ \ cmd\=\'gdate\''
'\ \ elif\ \[\[\ \"\$\{TRAVIS_OS_NAME\}\"\ \=\=\ osx\ \]\]\;\ then'
'\ \ \ \ format\=\'\+\%s000000000\''
'\ \ fi'
''
'\ \ \"\$\{cmd\}\"\ -u\ \"\$\{format\}\"'
'\}'
''
'travis_remove_from_path\(\)\ \{'
'\ \ local\ target\=\"\$1\"'
'\ \ PATH\=\"\$\(echo\ \"\$PATH\"\ \|'
'\ \ \ \ sed\ -e\ \"s,\\\\\(:\\\\\|\^\\\\\)\$target\\\\\(:\\\\\|\$\\\\\),:,g\"\ \\'
'\ \ \ \ \ \ -e\ \'s/::\\\+/:/g\'\ \\'
'\ \ \ \ \ \ -e\ \'s/:\$//\'\ \\'
'\ \ \ \ \ \ -e\ \'s/\^://\'\)\"'
'\}'
''
'travis_result\(\)\ \{'
'\ \ local\ result\=\"\$\{1\}\"'
'\ \ export\ TRAVIS_TEST_RESULT\=\$\(\(\$\{TRAVIS_TEST_RESULT:-0\}\ \|\ \$\(\(result\ \!\=\ 0\)\)\)\)'
''
'\ \ if\ \[\[\ \"\$\{result\}\"\ -eq\ 0\ \]\]\;\ then'
'\ \ \ \ printf\ \"\$\{ANSI_GREEN\}The\ command\ \\\"\%s\\\"\ exited\ with\ \$\{result\}.\$\{ANSI_RESET\}\\\\n\"\ \"\$\{TRAVIS_CMD\}\"'
'\ \ else'
'\ \ \ \ printf\ \"\$\{ANSI_RED\}The\ command\ \\\"\%s\\\"\ exited\ with\ \$\{result\}.\$\{ANSI_RESET\}\\\\n\"\ \"\$\{TRAVIS_CMD\}\"'
'\ \ fi'
'\}'
''
'travis_retry\(\)\ \{'
'\ \ local\ result\=0'
'\ \ local\ count\=1'
'\ \ while\ \[\[\ \"\$\{count\}\"\ -le\ 3\ \]\]\;\ do'
'\ \ \ \ \[\[\ \"\$\{result\}\"\ -ne\ 0\ \]\]\ \&\&\ \{'
'\ \ \ \ \ \ echo\ -e\ \"\\\\n\$\{ANSI_RED\}The\ command\ \\\"\$\{\*\}\\\"\ failed.\ Retrying,\ \$\{count\}\ of\ 3.\$\{ANSI_RESET\}\\\\n\"\ \>\&2'
'\ \ \ \ \}'
'\ \ \ \ \#\ run\ the\ command\ in\ a\ way\ that\ doesn\'t\ disable\ setting\ \`errexit\`'
'\ \ \ \ \"\$\{@\}\"'
'\ \ \ \ result\=\"\$\{\?\}\"'
'\ \ \ \ if\ \[\[\ \$result\ -eq\ 0\ \]\]\;\ then\ break\;\ fi'
'\ \ \ \ count\=\"\$\(\(count\ \+\ 1\)\)\"'
'\ \ \ \ sleep\ 1'
'\ \ done'
''
'\ \ \[\[\ \"\$\{count\}\"\ -gt\ 3\ \]\]\ \&\&\ \{'
'\ \ \ \ echo\ -e\ \"\\\\n\$\{ANSI_RED\}The\ command\ \\\"\$\{\*\}\\\"\ failed\ 3\ times.\$\{ANSI_RESET\}\\\\n\"\ \>\&2'
'\ \ \}'
''
'\ \ return\ \"\$\{result\}\"'
'\}'
''
'\#\ shellcheck\ disable\=SC1117'
''
'travis_setup_env\(\)\ \{'
'\ \ export\ ANSI_RED\=\"\\033\[31\;1m\"'
'\ \ export\ ANSI_GREEN\=\"\\033\[32\;1m\"'
'\ \ export\ ANSI_YELLOW\=\"\\033\[33\;1m\"'
'\ \ export\ ANSI_RESET\=\"\\033\[0m\"'
'\ \ export\ ANSI_CLEAR\=\"\\033\[0K\"'
''
'\ \ export\ DEBIAN_FRONTEND\=noninteractive'
''
'\ \ if\ \[\ \"\$\{TERM\}\"\ \=\ dumb\ \]\;\ then'
'\ \ \ \ unset\ TERM'
'\ \ fi'
'\ \ :\ \"\$\{SHELL:\=/bin/bash\}\"'
'\ \ :\ \"\$\{TERM:\=xterm\}\"'
'\ \ :\ \"\$\{USER:\=travis\}\"'
'\ \ export\ SHELL'
'\ \ export\ TERM'
'\ \ export\ USER'
''
'\ \ case\ \$\(uname\ \|\ tr\ \'\[:upper:\]\'\ \'\[:lower:\]\'\)\ in'
'\ \ linux\*\)'
'\ \ \ \ export\ TRAVIS_OS_NAME\=linux'
'\ \ \ \ \;\;'
'\ \ darwin\*\)'
'\ \ \ \ export\ TRAVIS_OS_NAME\=osx'
'\ \ \ \ \;\;'
'\ \ msys\*\)'
'\ \ \ \ export\ TRAVIS_OS_NAME\=windows'
'\ \ \ \ \;\;'
'\ \ freebsd\*\)'
'\ \ \ \ export\ TRAVIS_OS_NAME\=freebsd'
'\ \ \ \ \;\;'
'\ \ \*\)'
'\ \ \ \ export\ TRAVIS_OS_NAME\=notset'
'\ \ \ \ \;\;'
'\ \ esac'
''
'\ \ case\ \$\(uname\ -m\)\ in'
'\ \ x86_64\*\)'
'\ \ \ \ export\ TRAVIS_CPU_ARCH\=amd64'
'\ \ \ \ \;\;'
'\ \ aarch64\*\)'
'\ \ \ \ export\ TRAVIS_CPU_ARCH\=arm64'
'\ \ \ \ \;\;'
'\ \ ppc64le\*\)'
'\ \ \ \ export\ TRAVIS_CPU_ARCH\=ppc64le'
'\ \ \ \ \;\;'
'\ \ s390x\*\)'
'\ \ \ \ export\ TRAVIS_CPU_ARCH\=s390x'
'\ \ \ \ \;\;'
'\ \ \*\)'
'\ \ \ \ export\ TRAVIS_CPU_ARCH\=notset'
'\ \ \ \ \;\;'
'\ \ esac'
''
'\ \ export\ TRAVIS_DIST\=notset'
'\ \ export\ TRAVIS_INIT\=notset'
'\ \ TRAVIS_ARCH\=\"\$\(uname\ -m\)\"'
'\ \ if\ \[\[\ \"\$\{TRAVIS_ARCH\}\"\ \=\=\ x86_64\ \]\]\;\ then'
'\ \ \ \ TRAVIS_ARCH\=\'amd64\''
'\ \ fi'
'\ \ export\ TRAVIS_ARCH'
''
'\ \ if\ \[\[\ \"\$\{TRAVIS_OS_NAME\}\"\ \=\=\ linux\ \]\]\;\ then'
'\ \ \ \ TRAVIS_DIST\=\"\$\(lsb_release\ -sc\ 2\>/dev/null\ \|\|\ echo\ notset\)\"'
'\ \ \ \ export\ TRAVIS_DIST'
'\ \ \ \ if\ command\ -v\ systemctl\ \>/dev/null\ 2\>\&1\;\ then'
'\ \ \ \ \ \ export\ TRAVIS_INIT\=systemd'
'\ \ \ \ else'
'\ \ \ \ \ \ export\ TRAVIS_INIT\=upstart'
'\ \ \ \ fi'
'\ \ fi'
''
'\ \ export\ TRAVIS_TEST_RESULT\='
'\ \ export\ TRAVIS_CMD\='
''
'\ \ TRAVIS_TMPDIR\=\"\$\(mktemp\ -d\ 2\>/dev/null\ \|\|\ mktemp\ -d\ -t\ \'travis_tmp\'\)\"'
'\ \ mkdir\ -p\ \"\$\{TRAVIS_TMPDIR\}\"'
'\ \ export\ TRAVIS_TMPDIR'
''
'\ \ TRAVIS_INFRA\=unknown'
'\ \ if\ \[\[\ \"\$\{TRAVIS_ENABLE_INFRA_DETECTION\}\"\ \=\=\ true\ \]\]\;\ then'
'\ \ \ \ TRAVIS_INFRA\=\"\$\(travis_whereami\ \|\ awk\ -F\=\ \'/\^infra/\ \{\ print\ \$2\ \}\'\)\"'
'\ \ fi'
'\ \ export\ TRAVIS_INFRA'
''
'\ \ if\ command\ -v\ pgrep\ \&\>/dev/null\;\ then'
'\ \ \ \ pgrep\ -u\ \"\$\{USER\}\"\ 2\>/dev/null\ \|'
'\ \ \ \ \ \ grep\ -v\ -w\ \"\$\{\$\}\"\ \>\"\$\{TRAVIS_TMPDIR\}/pids_before\"\ \|\|\ true'
'\ \ fi'
'\}'
''
'travis_setup_java\(\)\ \{'
'\ \ local\ jdkpath\ jdk\ vendor\ version'
'\ \ jdk\=\"\$1\"'
'\ \ vendor\=\"\$2\"'
'\ \ version\=\"\$3\"'
'\ \ jdkpath\=\"\$\(travis_find_jdk_path\ \"\$jdk\"\ \"\$vendor\"\ \"\$version\"\)\"'
'\ \ if\ \[\[\ -z\ \"\$jdkpath\"\ \]\]\;\ then'
'\ \ \ \ if\ \[\[\ \"\$TRAVIS_OS_NAME\"\ \=\=\ osx\ \]\]\;\ then'
'\ \ \ \ \ \ java\ -version\ 2\>\&1\ \|\ awk\ -v\ vendor\=\"\$vendor\"\ -v\ version\=\"\$version\"\ -F\'\"\'\ \''
'\ \ \ \ \ \ \ \ BEGIN\ \{'
'\ \ \ \ \ \ \ \ \ \ v\ \=\ \"openjdk\"'
'\ \ \ \ \ \ \ \ \ \ if\(version\<9\)\ \{\ version\ \=\ \"1\\\\.\"version\ \}'
'\ \ \ \ \ \ \ \ \ \ version\ \=\ \"\^\"version\"\\\\.\"'
'\ \ \ \ \ \ \ \ \}'
'\ \ \ \ \ \ \ \ /HotSpot/\ \{\ v\ \=\ \"oracle\"\ \}'
'\ \ \ \ \ \ \ \ /version/\ \{\ if\ \(\$2\ \!\~\ version\)\ e\+\+\ \}'
'\ \ \ \ \ \ \ \ END\ \{'
'\ \ \ \ \ \ \ \ \ \ if\ \(vendor\ \!\=v\ \)\ e\+\+'
'\ \ \ \ \ \ \ \ \ \ exit\ e'
'\ \ \ \ \ \ \ \ \}'
'\ \ \ \ \ \ \'\ \&\&'
'\ \ \ \ \ \ \ \ return'
'\ \ \ \ fi'
'\ \ \ \ travis_install_jdk\ \"\$jdk\"\ \"\$vendor\"\ \"\$version\"'
'\ \ elif\ compgen\ -G\ \"\$\{jdkpath\%/\*\}/\$\(travis_jinfo_file\ \"\$vendor\"\ \"\$version\"\)\"\ \&\>/dev/null\ \&\&'
'\ \ \ \ declare\ -f\ jdk_switcher\ \&\>/dev/null\;\ then'
'\ \ \ \ travis_cmd\ \"jdk_switcher\ use\ \\\"\$jdk\\\"\"\ --echo\ --assert'
'\ \ \ \ if\ \[\[\ -f\ \~/.bash_profile.d/travis_jdk.bash\ \]\]\;\ then'
'\ \ \ \ \ \ sed\ -i\ \'/export\ \\\(PATH\\\|JAVA_HOME\\\)\=/d\'\ \~/.bash_profile.d/travis_jdk.bash'
'\ \ \ \ fi'
'\ \ else'
'\ \ \ \ export\ JAVA_HOME\=\"\$jdkpath\"'
'\ \ \ \ export\ PATH\=\"\$JAVA_HOME/bin:\$PATH\"'
'\ \ \ \ if\ \[\[\ -f\ \~/.bash_profile.d/travis_jdk.bash\ \]\]\;\ then'
'\ \ \ \ \ \ sed\ -i\ \"/export\ JAVA_HOME\=/s,\=.\\\\\+,\=\\\"\$JAVA_HOME\\\",\"\ \~/.bash_profile.d/travis_jdk.bash'
'\ \ \ \ fi'
'\ \ fi'
'\}'
''
'travis_temporary_hacks\(\)\ \{'
'\ \ if\ \[\[\ \!\ \"\$\{TRAVIS_OS_NAME\}\"\ \]\]\;\ then'
'\ \ \ \ return'
'\ \ fi'
''
'\ \ \"_travis_temporary_hacks_\$\{TRAVIS_OS_NAME\}\"\ \&\>/dev/null\ \|\|\ true'
'\}'
''
'_travis_temporary_hacks_linux\(\)\ \{'
'\ \ for\ troublesome_source\ in\ \\'
'\ \ \ \ rabbitmq-source.list\ \\'
'\ \ \ \ travis_ci_zeromq3.list\ \\'
'\ \ \ \ neo4j.list\;\ do'
'\ \ \ \ sudo\ rm\ -f\ \"\$\{TRAVIS_ROOT\}/etc/apt/sources.list.d/\$\{troublesome_source\}\"'
'\ \ done'
'\}'
''
'travis_terminate\(\)\ \{'
'\ \ if\ \[\[\ \!\ \"\$\{TRAVIS_OS_NAME\}\"\ \]\]\;\ then'
'\ \ \ \ return'
'\ \ fi'
''
'\ \ _travis_terminate_agent'
'\ \ \"_travis_terminate_\$\{TRAVIS_OS_NAME\}\"\ \"\$\{@\}\"'
'\}'
''
'_travis_terminate_linux\(\)\ \{'
'\ \ _travis_terminate_unix\ \"\$\{@\}\"'
'\}'
''
'_travis_terminate_osx\(\)\ \{'
'\ \ _travis_terminate_unix\ \"\$\{@\}\"'
'\}'
''
'_travis_terminate_freebsd\(\)\ \{'
'\ \ _travis_terminate_unix\ \"\$\{@\}\"'
'\}'
''
'_travis_terminate_unix\(\)\ \{'
'\ \ set\ \+e'
'\ \ \[\[\ \"\$\{TRAVIS_FILTERED\}\"\ \=\=\ redirect_io\ \&\&\ -e\ /dev/fd/9\ \]\]\ \&\&'
'\ \ \ \ sync\ \&\&'
'\ \ \ \ command\ exec\ 1\>\&9\ 2\>\&9\ 9\>\&-\ \&\&'
'\ \ \ \ sync'
'\ \ pgrep\ -u\ \"\$\{USER\}\"\ \|\ grep\ -v\ -w\ \"\$\{\$\}\"\ \>\"\$\{TRAVIS_TMPDIR\}/pids_after\"'
'\ \ awk\ \'NR\=\=FNR\{a\[\$1\]\+\+\;next\}\;\!\(\$1\ in\ a\)\'\ \"\$\{TRAVIS_TMPDIR\}\"/pids_\{before,after\}\ \|'
'\ \ \ \ xargs\ kill\ \&\>/dev/null\ \|\|\ true'
'\ \ pkill\ -9\ -P\ \"\$\{\$\}\"\ \&\>/dev/null\ \|\|\ true'
'\ \ exit\ \"\$\{1\}\"'
'\}'
''
'_travis_terminate_windows\(\)\ \{'
'\ \ \#\ TODO:\ find\ all\ child\ processes\ and\ exit\ via\ ...\ powershell\?'
'\ \ exit\ \"\$\{1\}\"'
'\}'
''
'_travis_terminate_agent\(\)\ \{'
'\ \ \[\ \!\ -f\ /tmp/travis/agent.pid\ \]\ \&\&\ return'
'\ \ pid\=\$\(cat\ /tmp/travis/agent.pid\)'
''
'\ \ kill\ \"\$pid\"\ \&\>/dev/null'
'\ \ counter\=500'
'\ \ while\ test\ \$\(\(counter--\)\)\ -ne\ 0\ -a\ -f\ /tmp/travis/agent.pid\;\ do'
'\ \ \ \ sleep\ 0.1'
'\ \ done'
''
'\ \ \[\ -z\ \$\{TRAVIS_AGENT_DEBUG\+x\}\ \]\ \&\&\ return'
'\ \ echo'
'\ \ travis_fold\ start\ agent.debug'
'\ \ echo\ \'cat\ /tmp/travis/agent.log\''
'\ \ cat\ /tmp/travis/agent.log'
'\ \ travis_fold\ end\ agent.debug'
'\}'
''
'travis_time_finish\(\)\ \{'
'\ \ local\ result\=\"\$\{\?\}\"'
'\ \ local\ travis_timer_end_time'
'\ \ local\ event\=\"\$\{1\}\"'
'\ \ travis_timer_end_time\=\"\$\(travis_nanoseconds\)\"'
'\ \ local\ duration'
'\ \ duration\=\"\$\(\(travis_timer_end_time\ -\ TRAVIS_TIMER_START_TIME\)\)\"'
'\ \ echo\ -en\ \"travis_time:end:\$\{TRAVIS_TIMER_ID\}:start\=\$\{TRAVIS_TIMER_START_TIME\},finish\=\$\{travis_timer_end_time\},duration\=\$\{duration\},event\=\$\{event\}\\\\r\$\{ANSI_CLEAR\}\"'
'\ \ return\ \"\$\{result\}\"'
'\}'
''
'travis_time_start\(\)\ \{'
'\ \ TRAVIS_TIMER_ID\=\"\$\(printf\ \%08x\ \$\(\(RANDOM\ \*\ RANDOM\)\)\)\"'
'\ \ TRAVIS_TIMER_START_TIME\=\"\$\(travis_nanoseconds\)\"'
'\ \ export\ TRAVIS_TIMER_ID\ TRAVIS_TIMER_START_TIME'
'\ \ echo\ -en\ \"travis_time:start:\$TRAVIS_TIMER_ID\\\\r\$\{ANSI_CLEAR\}\"'
'\}'
''
'travis_trace_span\(\)\ \{'
'\ \ local\ result\=\"\$\{\?\}\"'
'\ \ local\ template\=\"\$\{1\}\"'
'\ \ local\ timestamp'
'\ \ timestamp\=\"\$\(travis_nanoseconds\)\"'
'\ \ template\=\"\$\{template/__TRAVIS_TIMESTAMP__/\$\{timestamp\}\}\"'
'\ \ template\=\"\$\{template/__TRAVIS_STATUS__/\$\{result\}\}\"'
'\ \ echo\ \"\$\{template\}\"\ \>\>/tmp/build.trace'
'\ \ return\ \"\$\{result\}\"'
'\}'
''
'travis_vers2int\(\)\ \{'
'\ \ local\ args'
'\ \ read\ -r\ -a\ args\ \<\<\<\"\$\(echo\ \"\$\{1\}\"\ \|\ grep\ --only\ \'\^\[0-9\\.\]\[0-9\\.\]\*\'\ \|\ tr\ \'.\'\ \'\ \'\)\"'
'\ \ printf\ \'1\%03d\%03d\%03d\%03d\'\ \"\$\{args\[@\]\}\"'
'\}'
''
'travis_wait\(\)\ \{'
'\ \ local\ timeout\=\"\$\{1\}\"'
''
'\ \ if\ \[\[\ \"\$\{timeout\}\"\ \=\~\ \^\[0-9\]\+\$\ \]\]\;\ then'
'\ \ \ \ shift'
'\ \ else'
'\ \ \ \ timeout\=20'
'\ \ fi'
''
'\ \ local\ cmd\=\(\"\$\{@\}\"\)'
'\ \ local\ log_file\=\"travis_wait_\$\{\$\}.log\"'
''
'\ \ \"\$\{cmd\[@\]\}\"\ \&\>\"\$\{log_file\}\"\ \&'
'\ \ local\ cmd_pid\=\"\$\{\!\}\"'
''
'\ \ travis_jigger\ \"\$\{\!\}\"\ \"\$\{timeout\}\"\ \"\$\{cmd\[@\]\}\"\ \&'
'\ \ local\ jigger_pid\=\"\$\{\!\}\"'
'\ \ local\ result'
''
'\ \ \{'
'\ \ \ \ wait\ \"\$\{cmd_pid\}\"\ 2\>/dev/null'
'\ \ \ \ result\=\"\$\{\?\}\"'
'\ \ \ \ ps\ -p\"\$\{jigger_pid\}\"\ \&\>/dev/null\ \&\&\ kill\ \"\$\{jigger_pid\}\"'
'\ \ \}'
''
'\ \ if\ \[\[\ \"\$\{result\}\"\ -eq\ 0\ \]\]\;\ then'
'\ \ \ \ printf\ \"\\\\n\$\{ANSI_GREEN\}The\ command\ \%s\ exited\ with\ \$\{result\}.\$\{ANSI_RESET\}\\\\n\"\ \"\$\{cmd\[\*\]\}\"'
'\ \ else'
'\ \ \ \ printf\ \"\\\\n\$\{ANSI_RED\}The\ command\ \%s\ exited\ with\ \$\{result\}.\$\{ANSI_RESET\}\\\\n\"\ \"\$\{cmd\[\*\]\}\"'
'\ \ fi'
''
'\ \ echo\ -e\ \"\\\\n\$\{ANSI_GREEN\}Log:\$\{ANSI_RESET\}\\\\n\"'
'\ \ cat\ \"\$\{log_file\}\"'
''
'\ \ return\ \"\$\{result\}\"'
'\}'
''
'travis_whereami\(\)\ \{'
'\ \ curl\ -sSL\ -H\ \'Accept:\ text/plain\'\ \\'
'\ \ \ \ \"\$\{TRAVIS_WHEREAMI_URL:-https://whereami.travis-ci.com\}\"'
'\}'
' > ${TRAVIS_HOME}/.travis/functions
echo source\ \"\$\{TRAVIS_HOME\}/.travis/functions\"'
' > ${TRAVIS_HOME}/.travis/job_stages
source "${TRAVIS_HOME}/.travis/functions"
travis_setup_env
travis_temporary_hacks
# START_FUNCS
cat <<'EOFUNC_SETUP_FILTER' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_setup_filter() {
travis_time_start
for dir in $(echo $PATH | tr : " "); do
  test -d $dir && sudo chmod o-w $dir | grep changed
done

travis_time_finish no_world_writable_dirs
:
}

EOFUNC_SETUP_FILTER
cat <<'EOFUNC_CONFIGURE' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_configure() {
travis_time_start

if [[ "$TRAVIS_OS_NAME" = windows ]]; then
  echo
  echo -e "\033[33;1mThe language 'cpp' is currently unsupported on the Windows Build Environment.\033[0m"
  echo
  echo -e "\033[33;1mLet us know if you'd like to see it: https://travis-ci.community/c/environments/windows. Thanks for understanding!\033[0m"
  travis_terminate 1
fi

travis_time_finish check_unsupported
travis_time_start

travis_fold start system_info
  echo -e "\033[33;1mBuild system information\033[0m"
  echo -e "Build language: cpp"
  echo -e "Build dist: xenial"
  echo -e "Build id: ''"
  echo -e "Job id: ''"
  echo -e "Runtime kernel version: $(uname -r)"
  if [[ -f /usr/share/travis/system_info ]]; then
    cat /usr/share/travis/system_info
  fi
  if [[ -f /usr/local/travis/system_info ]]; then
    cat /usr/local/travis/system_info
  fi
travis_fold end system_info

echo
travis_time_finish show_system_info
travis_time_start
travis_cmd \ \ \ \ \ \ \ \ \ \ if\ \[\[\ -d\ /var/lib/apt/lists\ \&\&\ -n\ \$\(command\ -v\ apt-get\)\ \]\]\;\ then'
'\ \ \ \ \ \ \ \ \ \ \ \ grep\ -l\ -i\ -r\ basho\ /etc/apt/sources.list.d\ \|\ xargs\ sudo\ rm\ -f'
'\ \ \ \ \ \ \ \ \ \ fi'
' --event configure
travis_time_finish rm_riak_source
travis_time_start
travis_cmd \ \ \ \ \ \ \ \ \ \ if\ \[\[\ -d\ /var/lib/apt/lists\ \&\&\ -n\ \$\(command\ -v\ apt-get\)\ \]\]\;\ then'
'\ \ \ \ \ \ \ \ \ \ \ \ for\ f\ in\ \$\(grep\ -l\ -r\ rwky/redis\ /etc/apt/sources.list.d\)\;\ do'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ sed\ \'s,rwky/redis,rwky/ppa,g\'\ \$f\ \>\ /tmp/\$\{f\#\#\*\*/\}'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ sudo\ mv\ /tmp/\$\{f\#\#\*\*/\}\ /etc/apt/sources.list.d'
'\ \ \ \ \ \ \ \ \ \ \ \ done'
'\ \ \ \ \ \ \ \ \ \ fi'
' --event configure
travis_time_finish fix_rwky_redis
travis_time_start
travis_wait_for_network() {
  local wait_retries="${1}"
  local count=0
  shift
  local urls=("${@}")

  while [[ "${count}" -lt "${wait_retries}" ]]; do
    local confirmed=0
    for url in "${urls[@]}"; do
      if travis_download "${url}" /dev/null; then
        confirmed=$((confirmed + 1))
      fi
    done

    if [[ "${#urls[@]}" -eq "${confirmed}" ]]; then
      return
    fi

    count=$((count + 1))
    sleep 1
  done

  echo -e "${ANSI_RED}Timeout waiting for network availability.${ANSI_RESET}"
}

travis_cmd travis_wait_for_network\ 20\ \"http:///empty.txt\?job_id\=\&repo\=rlite/rlite\" --event configure
travis_time_finish wait_for_network
travis_time_start

if [[ "$TRAVIS_OS_NAME" == linux ]]; then
  travis_cmd export\ APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE\=1'
  'apt-key\ adv\ --list-public-keys\ --with-fingerprint\ --with-colons\ \|'
  '\ \ awk\ -F:\ \''
  '\ \ \ \ \ \ \$1\=\=\"pub\"\ \&\&\ \$2\~/\^\[er\]\$/\ \{\ state\=\"expired\"\ \}'
  '\ \ \ \ \ \ \$1\=\=\"fpr\"\ \&\&\ state\ \=\=\ \"expired\"\ \{'
  '\ \ \ \ \ \ \ \ out\ \=\ sprintf\(\"\%s\ \%s\",\ out,\ \$\(NF\ -1\)\)'
  '\ \ \ \ \ \ \ \ state\=\"valid\"'
  '\ \ \ \ \ \ \}'
  '\ \ \ \ \ \ END\ \{'
  '\ \ \ \ \ \ \ \ if\ \(length\(out\)\>0\)'
  '\ \ \ \ \ \ \ \ \ \ printf\ \"sudo\ apt-key\ adv\ --recv-keys\ --keyserver\ ha.pool.sks-keyservers.net\ \%s\",\ out'
  '\ \ \ \ \ \ \}'
  '\ \ \ \ \'\ \|'
  '\ \ bash\ \&\>/dev/null'
  ' --event configure
  travis_cmd if\ \[\[\ \(\ \"\$TRAVIS_DIST\"\ \=\=\ trusty\ \|\|\ \"\$TRAVIS_DIST\"\ \=\=\ precise\)\ \&\&\ -f\ /etc/init.d/rabbitmq-server\ \]\]\;\ then'
  '\ \ curl\ -sSL\ https:///files/gpg/rabbitmq-trusty.asc\ \|\ sudo\ apt-key\ add\ -'
  'fi\ \&\>/dev/null'
  ' --event configure
fi

travis_time_finish update_apt_keys
travis_time_start
travis_cmd \ \ \ \ \ \ \ \ \ \ \ \ if\ command\ -v\ lsb_release\;\ then'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ grep\ -l\ -i\ -r\ hhvm\ /etc/apt/sources.list.d\ \|\ xargs\ sudo\ rm\ -f'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ sudo\ sed\ -i\ /hhvm/d\ /etc/apt/sources.list'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ if\ \[\[\ \$\(lsb_release\ -cs\)\ \=\ trusty\ \]\]\;\ then'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ sudo\ apt-key\ adv\ --recv-keys\ --keyserver\ hkp://keyserver.ubuntu.com:80\ 0xB4112585D386EB94'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ sudo\ add-apt-repository\ \"deb\ \[arch\=amd64\]\ http://dl.hhvm.com/ubuntu\ \$\(lsb_release\ -sc\)\ main\"'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ fi'
'\ \ \ \ \ \ \ \ \ \ \ \ fi\ \&\>/dev/null'
' --event configure
travis_time_finish fix_hhvm_source
travis_time_start
travis_cmd \ \ \ \ \ \ \ \ \ \ \ \ if\ command\ -v\ lsb_release\ \&\>/dev/null\;\ then'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ shopt\ -s\ nullglob'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ for\ f\ in\ /etc/apt/sources.list.d/mongodb-\*.list\;\ do'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ grep\ -vq\ arch\=amd64\ \"\$f\"\ \&\&\ sudo\ sed\ -i\ \'s/\^deb\ /deb\ \[arch\=amd64\]\ /\'\ \"\$f\"'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ done'
'\ \ \ \ \ \ \ \ \ \ \ \ \ \ shopt\ -u\ nullglob'
'\ \ \ \ \ \ \ \ \ \ \ \ fi'
' --event configure
travis_time_finish update_mongo_arch
travis_time_start

if [[ $(uname) = Linux ]]; then
  if [[ $(lsb_release -sc 2>/dev/null) = trusty ]]; then
    travis_cmd unset\ _JAVA_OPTIONS --event configure
    travis_cmd unset\ MALLOC_ARENA_MAX --event configure
  fi
fi

travis_time_finish fix_sudo_enabled_trusty
travis_time_start
export PATH=$(echo $PATH | sed -e 's/::/:/g')
export PATH=$(echo -n $PATH | perl -e 'print join(":", grep { not $seen{$_}++ } split(/:/, scalar <>))')
travis_time_finish clean_up_path
travis_time_start
echo "options rotate
options timeout:1

nameserver 8.8.8.8
nameserver 8.8.4.4
nameserver 208.67.222.222
nameserver 208.67.220.220
" | sudo tee /etc/resolv.conf &> /dev/null
travis_time_finish fix_resolv_conf
travis_time_start
sudo sed -e 's/^\(127\.0\.0\.1.*\)$/\1 '`hostname`'/' -i'.bak' /etc/hosts 2> /dev/null
travis_time_finish fix_etc_hosts
travis_time_start

if [[ -f ~/.m2/settings.xml ]]; then
  travis_cmd sed\ -i\$\(\[\ \"\$TRAVIS_OS_NAME\"\ \=\=\ osx\ \]\ \&\&\ echo\ \"\ \"\).bak1\ -e\ \'s\|https://nexus.codehaus.org/snapshots/\|https://oss.sonatype.org/content/repositories/codehaus-snapshots/\|g\'\ \~/.m2/settings.xml --event configure
  travis_cmd sed\ -i\$\(\[\ \"\$TRAVIS_OS_NAME\"\ \=\=\ osx\ \]\ \&\&\ echo\ \"\ \"\).bak2\ -e\ \'s\|https://repository.apache.org/releases/\|https://repository.apache.org/content/repositories/releases/\|g\'\ \~/.m2/settings.xml --event configure
fi

travis_time_finish fix_mvn_settings_xml
travis_time_start
sed -e 's/^\([0-9a-f:]\+\s\)localhost/\1/' /etc/hosts > /tmp/hosts.tmp && cat /tmp/hosts.tmp | sudo tee /etc/hosts > /dev/null 2>&1
travis_time_finish no_ipv6_localhost
travis_time_start
test -f /etc/mavenrc && sudo sed -e 's/M2_HOME=\(.\+\)$/M2_HOME=${M2_HOME:-\1}/' -i'.bak' /etc/mavenrc
travis_time_finish fix_etc_mavenrc
travis_time_start

if [[ $(command -v sw_vers) ]]; then
  travis_cmd sudo\ security\ delete-certificate\ -Z\ 0950B6CD3D2F37EA246A1AAA20DFAADBD6FE1F75\ /Library/Keychains/System.keychain\ \&\>/dev/null --event configure
  travis_cmd wget\ -q\ https://developer.apple.com/certificationauthority/AppleWWDRCA.cer --event configure
  travis_cmd sudo\ security\ add-certificates\ -k\ /Library/Keychains/System.keychain\ AppleWWDRCA.cer\ \&\>/dev/null --event configure
fi

travis_time_finish fix_wwdr_certificate
travis_time_start
grep '^127\.0\.0\.1' /etc/hosts | sed -e 's/^127\.0\.0\.1\s\{1,\}\(.*\)/\1/g' | sed -e 's/localhost \(.*\)/\1/g' | tr "\n" " " > /tmp/hosts_127_0_0_1
sed '/^127\.0\.0\.1/d' /etc/hosts > /tmp/hosts_sans_127_0_0_1
cat /tmp/hosts_sans_127_0_0_1 | sudo tee /etc/hosts &> /dev/null
echo -n "127.0.0.1 localhost " | sudo tee -a /etc/hosts &> /dev/null
{ cat /tmp/hosts_127_0_0_1; echo; } | sudo tee -a /etc/hosts &> /dev/null
travis_time_finish put_localhost_first
travis_time_start
# apply :home_paths
for path_entry in ${TRAVIS_HOME}/.local/bin ${TRAVIS_HOME}/bin ; do
  if [[ ${PATH%%:*} != ${path_entry} ]] ; then
    export PATH="${path_entry}:$PATH"
  fi
done

travis_time_finish home_paths
travis_time_start
if [ ! $(uname|egrep 'Darwin|FreeBSD') ]; then echo update_initramfs=no | sudo tee -a /etc/initramfs-tools/update-initramfs.conf > /dev/null; fi
travis_time_finish disable_initramfs
travis_time_start
travis_disable_ssh_roaming() {
  mkdir -p "${TRAVIS_HOME}/.ssh"
  chmod 0700 "${TRAVIS_HOME}/.ssh"
  touch "${TRAVIS_HOME}/.ssh/config"
  echo -e "Host *\\n  UseRoaming no\\n" |
    cat - "${TRAVIS_HOME}/.ssh/config" >"${TRAVIS_HOME}/.ssh/config.tmp" &&
    mv "${TRAVIS_HOME}/.ssh/config.tmp" "${TRAVIS_HOME}/.ssh/config"
}

if [[ "$(sw_vers -productVersion 2>/dev/null | cut -d . -f 2)" -lt 12 ]]; then
  travis_disable_ssh_roaming
fi

travis_time_finish disable_ssh_roaming
travis_time_start
function travis_debug() {
echo -e "\033[31;1mThe debug environment is not available. Please contact support.\033[0m"
false
}
travis_time_finish debug_tools
travis_time_start

if [[ $(command -v brew) ]]; then
  travis_cmd brew\ cask\ uninstall\ oclint\ \&\>/dev/null --event configure
  if [[ $? == 0 ]]; then
    echo -e "Uninstalled oclint to prevent interference with other packages."
    echo -e "If you need oclint, you must explicitly install it."
  fi
  echo
fi

travis_time_finish uninstall_oclint
travis_time_start

if [[ $(command -v sw_vers) ]]; then
  travis_cmd rvm\ use\ \&\>/dev/null --event configure
fi

travis_time_finish rvm_use
travis_time_start
travis_cmd sudo\ rm\ -f\ /etc/boto.cfg --event configure
travis_time_finish rm_etc_boto_cfg
travis_time_start

if [[ -L /usr/lib/jvm/java-8-oracle-amd64 ]]; then
  travis_cmd sudo\ rm\ -f\ /usr/lib/jvm/java-8-oracle-amd64 --event configure
  if [[ -f ${TRAVIS_HOME}/.jdk_switcher_rc ]]; then
    travis_cmd source\ \$\{TRAVIS_HOME\}/.jdk_switcher_rc --event configure
  fi
  if [[ -f /opt/jdk_switcher/jdk_switcher.sh ]]; then
    travis_cmd source\ /opt/jdk_switcher/jdk_switcher.sh --event configure
  fi
fi

travis_time_finish rm_oraclejdk8_symlink
travis_time_start

if [[ $(uname -m) == x86_64 && $(command -v lsb_release) && $(lsb_release -cs) != precise ]]; then
  travis_cmd sudo\ dpkg\ --add-architecture\ i386 --event configure
fi

travis_time_finish enable_i386
travis_time_start

if [[ -n "${rvm_path}" ]]; then
  echo \#\!/bin/bash'
  'if\ \[\[\ \"\$\{rvm_ruby_string\}\"\ \=\~\ \"truffleruby\"\ \]\]\;\ then'
  '\ \ \#\ TruffleRuby\ always\ has\ a\ more\ recent\ RubyGems\ than\ 2.6.13.'
  '\ \ return\ 0'
  'fi'
  'gem\ --help\ \&\>/dev/null\ \|\|\ return\ 0'
  ''
  'travis_vers2int\(\)\ \{'
  '\ \ local\ args'
  '\ \ read\ -r\ -a\ args\ \<\<\<\"\$\(echo\ \"\$\{1\}\"\ \|\ grep\ --only\ \'\^\[0-9\\.\]\[0-9\\.\]\*\'\ \|\ tr\ \'.\'\ \'\ \'\)\"'
  '\ \ printf\ \'1\%03d\%03d\%03d\%03d\'\ \"\$\{args\[@\]\}\"'
  '\}'
  ''
  ''
  'if\ \[\[\ \"\$\(travis_vers2int\ \"\$\(gem\ --version\)\"\)\"\ -lt\ \"\$\(travis_vers2int\ \"2.6.13\"\)\"\ \]\]\;\ then'
  '\ \ echo\ \"\"'
  '\ \ echo\ -e\ \"\\033\[32\;1m\*\*\ Updating\ RubyGems\ to\ the\ latest\ compatible\ version\ for\ security\ reasons.\ \*\*\\033\[0m\"'
  '\ \ echo\ -e\ \"\\033\[32\;1m\*\*\ If\ you\ need\ an\ older\ version,\ you\ can\ downgrade\ with\ \'gem\ update\ --system\ OLD_VERSION\'.\ \*\*\\033\[0m\"'
  '\ \ echo\ \"\"'
  '\ \ if\ \[\[\ \"\$\(travis_vers2int\ \"\$\(ruby\ -e\ \'puts\ RUBY_VERSION\'\)\"\)\"\ -lt\ \"\$\(travis_vers2int\ \"2.3.0\"\)\"\ \]\]\;\ then'
  '\ \ \ \ gem\ update\ --system\ 2.7.8\ \&\>/dev/null'
  '\ \ else'
  '\ \ \ \ gem\ update\ --system\ \&\>/dev/null'
  '\ \ fi'
  'fi'
  ' > ${TRAVIS_HOME}/.rvm/hooks/after_use
  if [[ -f ${TRAVIS_HOME}/.rvm/hooks/after_use ]]; then
    chmod +x ${TRAVIS_HOME}/.rvm/hooks/after_use
  fi
fi

travis_time_finish update_rubygems
travis_time_start
[[ -n "$(yarn global bin 2>/dev/null | grep /)" && ! :$PATH: =~ :$(yarn global bin 2>/dev/null | grep /): ]] && export PATH="$PATH:$(yarn global bin 2>/dev/null | grep /)"

travis_time_finish ensure_path_components
travis_time_start
function curl() {
  command curl --retry 2 -sS "$@"
}

travis_time_finish redefine_curl
travis_time_start
if [[ $TRAVIS_FILTERED = redirect_io ]]; then
  cat <<\EOPY >~/nonblock.py
import os
import sys
import fcntl

flags_stdout = fcntl.fcntl(sys.stdout, fcntl.F_GETFL)
fcntl.fcntl(sys.stdout, fcntl.F_SETFL, flags_stdout&~os.O_NONBLOCK)

flags_stderr = fcntl.fcntl(sys.stderr, fcntl.F_GETFL)
fcntl.fcntl(sys.stderr, fcntl.F_SETFL, flags_stderr&~os.O_NONBLOCK)
EOPY
  python ~/nonblock.py
  rm ~/nonblock.py
fi

travis_time_finish nonblock_pipe
travis_time_start
declare -a _TRAVIS_APT_MIRRORS_BY_INFRASTRUCTURE
_TRAVIS_APT_MIRRORS_BY_INFRASTRUCTURE+=(ec2::http://us-east-1.ec2.archive.ubuntu.com/ubuntu/)
_TRAVIS_APT_MIRRORS_BY_INFRASTRUCTURE+=(gce::http://us-central1.gce.archive.ubuntu.com/ubuntu/)
_TRAVIS_APT_MIRRORS_BY_INFRASTRUCTURE+=(packet::http://archive.ubuntu.com/ubuntu/)
_TRAVIS_APT_MIRRORS_BY_INFRASTRUCTURE+=(unknown::http://archive.ubuntu.com/ubuntu/)
travis_munge_apt_sources() {
  if ! command -v apt-get &>/dev/null; then
    return
  fi

  local src="${TRAVIS_ROOT}/etc/apt/sources.list"
  src="${src//\/\//\/}"
  local tmp_dest="${TRAVIS_TMPDIR}/etc-apt-sources.list"
  tmp_dest="${tmp_dest//\/\//\/}"

  if [[ ! -f "${src}" ]]; then
    return
  fi

  local mirror
  for entry in "${_TRAVIS_APT_MIRRORS_BY_INFRASTRUCTURE[@]}"; do
    if [[ "${entry%%::*}" == "${TRAVIS_INFRA}" ]]; then
      mirror="${entry##*::}"
    fi
  done

  if [[ ! "${mirror}" ]]; then
    return
  fi

  sed -e "s,http://.*\\.ubuntu\\.com/ubuntu/,${mirror}," \
    "${src}" >"${tmp_dest}"
  sudo mv "${src}" "${src}.travis-build.bak"
  sudo mv "${tmp_dest}" "${src}"
}

travis_munge_apt_sources
travis_setup_apt_proxy() {
  if [[ ! "${TRAVIS_APT_PROXY}" ]]; then
    return
  fi

  local dest_dir='/etc/apt/apt.conf.d'

  if [[ ! -d "${dest_dir}" ]]; then
    return
  fi

  if ! sudo -n echo &>/dev/null; then
    return
  fi

  if ! curl --connect-timeout 1 -fsSL -o /dev/null \
    "${TRAVIS_APT_PROXY}/__squignix_health__" &>/dev/null; then
    return
  fi

  (
    cat <<EOCONF
Acquire::http::Proxy "${TRAVIS_APT_PROXY}";
Acquire::https::Proxy false;
Acquire::http::Proxy::download.oracle.com "DIRECT";
Acquire::https::Proxy::download.oracle.com "DIRECT";
Acquire::http::Proxy::*.java.net "DIRECT";
Acquire::https::Proxy::*.java.net "DIRECT";
Acquire::http::Proxy::apt.postgresql.org "DIRECT";
Acquire::https::Proxy::apt.postgresql.org "DIRECT";
EOCONF
  ) | sudo tee "${dest_dir}/99-travis-apt-proxy" &>/dev/null
}

travis_setup_apt_proxy
travis_time_finish apt_get_update
travis_time_start
travis_time_finish deprecate_xcode_64
travis_time_start

if [[ ("$TRAVIS_DIST" != precise || "$TRAVIS_OS_NAME" == linux) && "$(which heroku)" =~ heroku ]]; then
  travis_cmd sudo\ bash\ -c\ \''
  '\ \ cd\ /usr/lib'
  '\ \ \(curl\ -sfSL\ https://cli-assets.heroku.com/heroku-linux-x64.tar.xz\ \|\ tar\ Jx\)\ \&\&'
  '\ \ ln\ -sf\ /usr/lib/heroku/bin/heroku\ /usr/bin/heroku'
  '\''
  ' --event configure
  if [[ $? -eq 0 ]]; then
    travis_cmd sudo\ bash\ -c\ \''
    '\ \ rm\ -rf\ /usr/local/heroku'
    '\ \ apt-get\ purge\ -y\ heroku-toolbelt\ heroku\ \&\>/dev/null'
    '\''
    ' --event configure
  else
    echo -e "\033[31;1mFailed to update Heroku CLI\033[0m"
  fi
fi

travis_time_finish update_heroku
travis_time_start
if [ "$TRAVIS_OS_NAME" = osx ] && ! declare -f shell_session_update >/dev/null; then
  shell_session_update() { :; }
  export -f shell_session_update
fi

travis_time_finish shell_session_update
travis_time_start

travis_fold start docker_mtu
  sudo test -f /etc/docker/daemon.json
  if [[ $? = 0 ]]; then
    echo '[{"op":"add","path":"/mtu","value":1460}]' > mtu.jsonpatch
    sudo jsonpatch /etc/docker/daemon.json mtu.jsonpatch > daemon.json
    sudo mv daemon.json /etc/docker/daemon.json
  else
    echo '{"mtu":1460}' | sudo tee /etc/docker/daemon.json > /dev/null
  fi
  
  sudo service docker restart
travis_fold end docker_mtu

travis_time_finish set_docker_mtu
travis_time_start

if sudo service resolvconf status >&/dev/null; then
  travis_fold start resolvconf
      echo "options timeout:1"  | sudo tee -a /etc/resolvconf/resolv.conf.d/tail >/dev/null
      echo "options attempts:3" | sudo tee -a /etc/resolvconf/resolv.conf.d/tail >/dev/null
      sudo service resolvconf restart
  travis_fold end resolvconf
fi

travis_time_finish resolvconf
travis_time_start
travis_maven_https() {
  if [[ ! -f $HOME/.m2/settings.xml ]]; then return; fi

  ruby -rrexml/document -e "begin
    doc=REXML::Document.new(File.read('$HOME/.m2/settings.xml'));
    doc.get_elements('//url[starts-with(.,\"http://\")]').each do |e|
      url = e.text
      e.text = url.gsub('http://','https://')
    end
    doc.write
  rescue
    nil
  end" >settings.xml
  if [[ -s settings.xml ]]; then
    mv settings.xml "${HOME}"/.m2/settings.xml
  fi
}

travis_maven_https
travis_time_finish maven_https
:
}

EOFUNC_CONFIGURE
cat <<'EOFUNC_PREPARE' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_prepare() {
travis_time_start
export PS4=+
travis_time_finish fix_ps4
:
}

EOFUNC_PREPARE
cat <<'EOFUNC_DISABLE_SUDO' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_disable_sudo() {
:
}

EOFUNC_DISABLE_SUDO
cat <<'EOFUNC_CHECKOUT' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_checkout() {
travis_time_start
export GIT_ASKPASS=echo
echo

travis_fold start git.checkout
  if [[ ! -d rlite/rlite/.git ]]; then
    travis_cmd git\ clone\ --depth\=50\ --branch\=\'\'\ https://github.com/rlite/rlite.git\ rlite/rlite --echo --retry --timing --event checkout
  else
    travis_cmd git\ -C\ rlite/rlite\ fetch\ origin --assert --echo --retry --timing --event checkout
    travis_cmd git\ -C\ rlite/rlite\ reset\ --hard --assert --echo --event checkout
  fi
  travis_cmd cd\ rlite/rlite --echo
  travis_cmd git\ checkout\ -qf\  --assert --echo --event checkout
travis_fold end git.checkout

echo

if [[ -f .gitmodules ]]; then
  travis_fold start git.submodule
    echo Host\ github.com'
    '\	StrictHostKeyChecking\ no'
    ' >> ~/.ssh/config
    travis_cmd git\ submodule\ update\ --init\ --recursive --assert --echo --retry --timing --event checkout
  travis_fold end git.submodule
fi

travis_time_finish checkout
:
}

EOFUNC_CHECKOUT
cat <<'EOFUNC_EXPORT' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_export() {
travis_time_start
export TRAVIS=true
export CI=true
export CONTINUOUS_INTEGRATION=true
export PAGER=cat
export HAS_JOSH_K_SEAL_OF_APPROVAL=true
export TRAVIS_ALLOW_FAILURE=''
export TRAVIS_EVENT_TYPE=''
export TRAVIS_PULL_REQUEST=false
export TRAVIS_SECURE_ENV_VARS=false
export TRAVIS_BUILD_ID=''
export TRAVIS_BUILD_NUMBER=''
export TRAVIS_BUILD_DIR=${HOME}/build/rlite/rlite
export TRAVIS_BUILD_WEB_URL=https:///rlite/rlite/builds/
export TRAVIS_JOB_ID=''
export TRAVIS_JOB_NAME=''
export TRAVIS_JOB_NUMBER=''
export TRAVIS_JOB_WEB_URL=https:///rlite/rlite/jobs/
export TRAVIS_BRANCH=''
export TRAVIS_COMMIT=''
export TRAVIS_COMMIT_MESSAGE=$(test -d .git && git log --format=%B -n 1 | head -c 32768)
export TRAVIS_COMMIT_RANGE=''
export TRAVIS_REPO_SLUG=rlite/rlite
export TRAVIS_OSX_IMAGE=''
export TRAVIS_LANGUAGE=cpp
export TRAVIS_TAG=''
export TRAVIS_SUDO=true
export TRAVIS_BUILD_STAGE_NAME=''
export TRAVIS_PULL_REQUEST_BRANCH=''
export TRAVIS_PULL_REQUEST_SHA=''
export TRAVIS_PULL_REQUEST_SLUG=''
travis_time_finish env
travis_cmd export\ TRAVIS_COMPILER\=g\+\+ --echo
travis_cmd export\ CXX\=\$\{CXX:-g\+\+\} --echo
travis_cmd export\ CXX_FOR_BUILD\=\$\{CXX_FOR_BUILD:-g\+\+\} --echo
travis_cmd export\ CC\=\$\{CC:-gcc\} --echo
travis_cmd export\ CC_FOR_BUILD\=\$\{CC_FOR_BUILD:-gcc\} --echo
:
}

EOFUNC_EXPORT
cat <<'EOFUNC_SETUP' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_setup() {
:
}

EOFUNC_SETUP
cat <<'EOFUNC_SETUP_CASHER' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_setup_casher() {
:
}

EOFUNC_SETUP_CASHER
cat <<'EOFUNC_SETUP_CACHE' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_setup_cache() {
:
}

EOFUNC_SETUP_CACHE
cat <<'EOFUNC_USE_WORKSPACES' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_use_workspaces() {
:
}

EOFUNC_USE_WORKSPACES
cat <<'EOFUNC_ANNOUNCE' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_announce() {
travis_cmd g\+\+\ --version --echo
:
}

EOFUNC_ANNOUNCE
cat <<'EOFUNC_DEBUG' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_debug() {
:
}

EOFUNC_DEBUG
cat <<'EOFUNC_BEFORE_INSTALL' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_before_install() {

travis_fold start before_install.1
  travis_cmd sudo\ apt-get\ -qq\ update --assert --echo --timing --event before_install
travis_fold end before_install.1

travis_fold start before_install.2
  travis_cmd sudo\ apt-get\ install\ -y\ gcc --assert --echo --timing --event before_install
travis_fold end before_install.2

travis_fold start before_install.3
  travis_cmd sudo\ apt-get\ install\ -y\ g\+\+ --assert --echo --timing --event before_install
travis_fold end before_install.3

travis_fold start before_install.4
  travis_cmd sudo\ apt-get\ install\ -y\ libprotobuf-dev --assert --echo --timing --event before_install
travis_fold end before_install.4

travis_fold start before_install.5
  travis_cmd sudo\ apt-get\ install\ -y\ protobuf-compiler --assert --echo --timing --event before_install
travis_fold end before_install.5

travis_fold start before_install.6
  travis_cmd sudo\ apt-get\ install\ -y\ cmake --assert --echo --timing --event before_install
travis_fold end before_install.6

travis_fold start before_install.7
  travis_cmd sudo\ apt-get\ install\ -y\ python --assert --echo --timing --event before_install
travis_fold end before_install.7

travis_fold start before_install.8
  travis_cmd sudo\ apt-get\ install\ -y\ bc --assert --echo --timing --event before_install
travis_fold end before_install.8

travis_fold start before_install.9
  travis_cmd sudo\ apt-get\ install\ -y\ kmod --assert --echo --timing --event before_install
travis_fold end before_install.9

travis_fold start before_install.10
  travis_cmd sudo\ apt-get\ install\ -y\ linux-headers-\$\(uname\ -r\) --assert --echo --timing --event before_install
travis_fold end before_install.10

:
}

EOFUNC_BEFORE_INSTALL
cat <<'EOFUNC_INSTALL' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_install() {
:
}

EOFUNC_INSTALL
cat <<'EOFUNC_BEFORE_SCRIPT' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_before_script() {
:
}

EOFUNC_BEFORE_SCRIPT
cat <<'EOFUNC_SCRIPT' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_script() {
travis_cmd ./configure --echo --timing --event script
travis_result $?
travis_cmd make --echo --timing --event script
travis_result $?
travis_cmd make\ test --echo --timing --event script
travis_result $?
travis_cmd sudo\ make\ install --echo --timing --event script
travis_result $?
travis_cmd sudo\ make\ depmod --echo --timing --event script
travis_result $?
travis_cmd sudo\ make\ intest --echo --timing --event script
travis_result $?
travis_cmd ./configure\ --debug --echo --timing --event script
travis_result $?
travis_cmd make --echo --timing --event script
travis_result $?
travis_cmd make\ test --echo --timing --event script
travis_result $?
travis_cmd sudo\ make\ install --echo --timing --event script
travis_result $?
travis_cmd sudo\ make\ depmod --echo --timing --event script
travis_result $?
travis_cmd sudo\ make\ intest --echo --timing --event script
travis_result $?
:
}

EOFUNC_SCRIPT
cat <<'EOFUNC_BEFORE_CACHE' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_before_cache() {
:
}

EOFUNC_BEFORE_CACHE
cat <<'EOFUNC_CREATE_WORKSPACES' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_create_workspaces() {
:
}

EOFUNC_CREATE_WORKSPACES
cat <<'EOFUNC_CACHE' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_cache() {
echo
:
}

EOFUNC_CACHE
cat <<'EOFUNC_RESET_STATE' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_reset_state() {
:
}

EOFUNC_RESET_STATE
cat <<'EOFUNC_AFTER_SUCCESS' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_after_success() {
:
}

EOFUNC_AFTER_SUCCESS
cat <<'EOFUNC_AFTER_FAILURE' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_after_failure() {
:
}

EOFUNC_AFTER_FAILURE
cat <<'EOFUNC_AFTER_SCRIPT' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_after_script() {
:
}

EOFUNC_AFTER_SCRIPT
cat <<'EOFUNC_FINISH' >>${TRAVIS_HOME}/.travis/job_stages
function travis_run_finish() {
:
}

EOFUNC_FINISH
# END_FUNCS
source ${TRAVIS_HOME}/.travis/job_stages
travis_run_setup_filter
travis_run_configure
travis_run_prepare
travis_run_disable_sudo
travis_run_checkout
travis_run_export
travis_run_setup
travis_run_setup_casher
travis_run_setup_cache
travis_run_use_workspaces
travis_run_announce
travis_run_debug
travis_run_before_install
travis_run_install
travis_run_before_script
travis_run_script
travis_run_before_cache
travis_run_create_workspaces
travis_run_cache
travis_run_after_success
travis_run_after_failure
travis_run_after_script
travis_run_finish
travis_cleanup
travis_footer
