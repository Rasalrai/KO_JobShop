# Job Shop
## Combinatorial Optimization project
### How to build/run
`cd ok_jobshop`

`g++ jobshop/main.cpp jobshop/input_output.cpp jobshop/solution.cpp -o jobshop.out`

`./jobshop.out test_file instance_type exec_time max_tasks result_file`
`test_file` - path to file with test instance

`instance_type` (`b` or `t`) - Beasley's or Tailard's instance format

`exec_time` - execution time in seconds; default=300

`max_tasks` - limits number of tasks for every job, 0 is whole file; default=0

`result_file` - name or path to file where you want your result to be saved,
if the file exists it will be overwritten; default=`wynik.txt`
