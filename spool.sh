#!/bin/bash

for i in {0..9}; do
	echo "./example -i test.yaml -o /data/HD5/tnivarthi/test-al-box-parallel-${i}.root"
done|parallel --no-notice -j 10 {}

hadd -f /data/HD5/tnivarthi/test-al-box-merged.root /data/HD5/tnivarthi/test-al-box-parallel-*.root
rm /data/HD5/tnivarthi/test-al-box-parallel-*.root
