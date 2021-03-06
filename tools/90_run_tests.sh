#!/bin/sh

set -e
set -u

cleanup() {
	${ncat_pid+kill ${ncat_pid}}
}
trap cleanup EXIT INT TERM

readonly script_path="$(cd "$(dirname "$0")" && pwd)"

"${script_path}/80_ads_route.sh"
"${script_path}/91_test_AdsTool.sh"

# setup fake ads server and install cleanup trap
nc -l 48898 -k &
ncat_pid=$!

# wait for fake ads server to accept connections
while ! nc -z localhost 48898; do sleep 1; done

# transitional hack to test meson or legacy build binaries
ln -s build/AdsLibTest AdsLibTest.bin || true
ln -s build/AdsLibOOITest AdsLibOOITest.bin || true
ln -s build/example example/example.bin || true

./AdsLibTest.bin
./AdsLibOOITest.bin
./example/example.bin
