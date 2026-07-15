# Green Efficiency Analysis

## Measurement Methodology

I measured the execution time of the provided C programs using the `clock()` function from the C standard library. All programs were compiled with the required compiler flags, and the measurements were performed on the same machine to keep the conditions consistent.

For the baseline experiment, I executed the program three times. The recorded execution times were **0.233516 s**, **0.241677 s**, and **0.234152 s**. Running the same program multiple times showed that the execution time changes slightly between runs even though the program and input remain the same.

For the algorithm comparison experiment, I measured both implementations three times. The average execution time was approximately **2.714067 seconds** for the naive algorithm and **0.000112 seconds** for the single-pass algorithm.

For the instrumentation experiment, the measured times were **0.000367 seconds** for building the dataset, **0.000406 seconds** for processing the data, **0.000192 seconds** for reducing the checksum, and **0.000972 seconds** for the total execution time.

## Observed Performance Differences

The biggest difference was between the naive algorithm and the single-pass algorithm. Although both programs solved the same problem correctly, the naive version was much slower. Based on the average execution times, it was about **24,161 times slower** than the single-pass implementation.

The instrumentation results also showed that the processing phase took the longest time, while the checksum reduction phase was the fastest. As expected, the total execution time was greater than each individual phase.

## Relation Between Runtime and Energy Consumption

This project did not measure actual power consumption, but execution time can be used as an indicator of CPU activity. A program that runs for a longer time usually keeps the processor busy for longer, which can increase energy usage. Since the single-pass algorithm finished much faster than the naive algorithm, it would generally be expected to use less energy on the same hardware.

## Limitations of the Experiment

One limitation is that the experiments were performed on only one computer, so background processes may have affected the timings. Another limitation is that `clock()` measures CPU time instead of actual electrical power consumption. The programs were also tested with only one dataset size.

## Practical Engineering Takeaway

This project showed that measuring performance is important before making conclusions about efficiency. The results clearly demonstrate that choosing a better algorithm has a much bigger effect than making small code changes. Using efficient algorithms can reduce execution time, improve performance, and help make software more energy efficient.
