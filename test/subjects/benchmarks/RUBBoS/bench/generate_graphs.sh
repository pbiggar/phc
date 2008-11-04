#!/bin/sh

# $1 is the report directory with the trailing /
# $2 is the Gnuplot terminal to use (gif, jpeg, ...)
# $3 is the number of clients

if [ -d $1 ]; then
  # Generate data files
  gunzip $1"db_server.gz"
  gunzip $1"web_server.gz"
  if [ -f $1"cjdbc_server.gz" ]; then
      gunzip $1"cjdbc_server.gz"
  fi
  if [ -f $1"cjdbc_server" ]; then
      bench/format_sar_output.awk $1"cjdbc_server"
      # Not forked as we check for this file later. This removes a
      # potential race
      gzip -9 $1"cjdbc_server"
  else
    echo "No CJDBC Server log files present";
  fi
  bench/format_sar_output.awk $1"db_server"
  bench/format_sar_output.awk $1"web_server"
  gzip -9 $1"db_server" &
  gzip -9 $1"web_server" &
  for ((i = 0 ; i < $3 ; i = i + 1)); do
    gunzip $1client$i.gz
    bench/format_sar_output.awk $1client$i
    gzip -9 $1client$i &
  done
  tmpFile=$1"gnuplot_input"
  rm -f $tmpFile

  #################################
  ## Graphs for DB & Web servers ##
  #################################

  # Plot CPU idle time
  echo "Generating servers CPU idle time graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cpu_idle.$2'"' >> $tmpFile;
  echo 'set title "Processor idle time"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Processor idle time in %"' >> $tmpFile;
  echo "set yrange [0:100]" >> $tmpFile;
  echo plot '"'$1db_server.cpu.idle.dat'"' title '"'Database'"' with lines, '"'$1web_server.cpu.idle.dat'"' title '"'Frontend'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot CPU busy time 
  echo "Generating servers CPU busy time graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cpu_busy.$2'"' >> $tmpFile;
  echo 'set title "Processor usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Processor usage in %"' >> $tmpFile;
  echo "set yrange [0:100]" >> $tmpFile;
  echo plot '"'$1db_server.cpu.busy.dat'"' title '"'Database'"' with lines, '"'$1web_server.cpu.busy.dat'"' title '"'Frontend'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot CPU user/system time
  echo "Generating servers CPU user/system time graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cpu_user_kernel.$2'"' >> $tmpFile;
  echo 'set title "User/Kernel processor usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Processor usage in %"' >> $tmpFile;
  echo "set yrange [0:100]" >> $tmpFile;
  echo plot '"'$1db_server.cpu.user.dat'"' title '"'Database user'"' with lines, '"'$1db_server.cpu.system.dat'"' title '"'Database kernel'"' with lines, '"'$1web_server.cpu.user.dat'"' title '"'Frontend user'"' with lines, '"'$1web_server.cpu.system.dat'"' title '"'Frontend kernel'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Processes/second
  echo "Generating servers Processes/second graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1procs.$2'"' >> $tmpFile;
  echo 'set title "Processes created"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of processes created per second"' >> $tmpFile;
  echo plot '"'$1db_server.proc.dat'"' title '"'Database'"' with lines, '"'$1web_server.proc.dat'"' title '"'Frontend'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Context switches/second
  echo "Generating servers Context switches/second graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1ctxtsw.$2'"' >> $tmpFile;
  echo 'set title "Context switches"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of context switches per second"' >> $tmpFile;
  echo plot '"'$1db_server.ctxsw.dat'"' title '"'Database'"' with lines, '"'$1web_server.ctxsw.dat'"' title '"'Frontend'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Disk total transfers
  echo "Generating servers Disk total transfers graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1disk_tps.$2'"' >> $tmpFile;
  echo 'set title "Disk transfers"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of disk transfers per second"' >> $tmpFile;
  echo plot '"'$1db_server.disk.tps.dat'"' title '"'Database'"' with lines, '"'$1web_server.disk.tps.dat'"' title '"'Frontend'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot disk read/write requests
  echo "Generating servers disk read/write requests graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1disk_rw_req.$2'"' >> $tmpFile;
  echo 'set title "Read/Write disk requests"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of requests per second"' >> $tmpFile;
  echo plot '"'$1db_server.disk.rtps.dat'"' title '"'Database read'"' with lines, '"'$1db_server.disk.wtps.dat'"' title '"'Database write'"' with lines, '"'$1web_server.disk.rtps.dat'"' title '"'Frontend read'"' with lines, '"'$1web_server.disk.wtps.dat'"' title '"'Frontend write'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot disk blocks read/write requests
  echo "Generating servers disk blocks read/write requests graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1disk_rw_req.$2'"' >> $tmpFile;
  echo 'set title " Disk blocks read/write requests"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of blocks per second"' >> $tmpFile;
  echo plot '"'$1db_server.disk.brdps.dat'"' title '"'Database read'"' with lines, '"'$1db_server.disk.bwrps.dat'"' title '"'Database write'"' with lines, '"'$1web_server.disk.brdps.dat'"' title '"'Frontend read'"' with lines, '"'$1web_server.disk.bwrps.dat'"' title '"'Frontend write'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Memory usage
  echo "Generating servers Memory usage graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1mem_usage.$2'"' >> $tmpFile;
  echo 'set title "Memory usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Amount of memory in KB"' >> $tmpFile;
  echo plot '"'$1db_server.mem.kbmemused.dat'"' title '"'Database'"' with lines, '"'$1web_server.mem.kbmemused.dat'"' title '"'Frontend'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Memory & cache usage
  echo "Generating servers Memory & cache usage graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1mem_cache.$2'"' >> $tmpFile;
  echo 'set title "Memory & cache usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Amount of memory in KB"' >> $tmpFile;
  echo plot '"'$1db_server.mem.kbmemused.dat'"' title '"'Database memory'"' with lines, '"'$1web_server.mem.kbmemused.dat'"' title '"'Frontend memory'"' with lines, '"'$1db_server.mem.kbcached.dat'"' title '"'Database cache'"' with lines, '"'$1web_server.mem.kbcached.dat'"' title '"'Frontend cache'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot network received/transmitted packets
  echo "Generating servers network received/transmitted packets graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1net_rt_pack.$2'"' >> $tmpFile;
  echo 'set title "Network received/transmitted packets"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of packets per second"' >> $tmpFile;
  echo plot '"'$1db_server.net.rxpck.dat'"' title '"'Database received'"' with lines, '"'$1db_server.net.txpck.dat'"' title '"'Database transmitted'"' with lines, '"'$1web_server.net.rxpck.dat'"' title '"'Frontend received'"' with lines, '"'$1web_server.net.txpck.dat'"' title '"'Frontend transmitted'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot network received/transmitted bytes
  echo "Generating servers network received/transmitted bytes graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1net_rt_byt.$2'"' >> $tmpFile;
  echo 'set title "Network received/transmitted bytes"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of bytes per second"' >> $tmpFile;
  echo plot '"'$1db_server.net.rxbyt.dat'"' title '"'Database received'"' with lines, '"'$1db_server.net.txbyt.dat'"' title '"'Database transmitted'"' with lines, '"'$1web_server.net.rxbyt.dat'"' title '"'Frontend received'"' with lines, '"'$1web_server.net.txbyt.dat'"' title '"'Frontend transmitted'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Sockets usage
  echo "Generating servers Sockets usage graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1socks.$2'"' >> $tmpFile;
  echo 'set title "Sockets"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Number of sockets"' >> $tmpFile;
  echo plot '"'$1db_server.sock.totsck.dat'"' title '"'Database'"' with lines, '"'$1web_server.sock.totsck.dat'"' title '"'Frontend'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile


  ########################
  ## Graphs for clients ##
  ########################

  # Plot CPU idle time
  echo "Generating clients CPU idle time graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_cpu_idle.$2'"' >> $tmpFile;
  echo 'set title "Processor idle time"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Processor idle time in %"' >> $tmpFile;
  echo "set yrange [0:100]" >> $tmpFile;
  echo -n plot '"'$1client0.cpu.idle.dat'"' title '"'Main client'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.cpu.idle.dat'"' title '"'Remote client $i'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot CPU busy time 
  echo "Generating clients CPU busy time graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_cpu_busy.$2'"' >> $tmpFile;
  echo 'set title "Processor usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Processor usage in %"' >> $tmpFile;
  echo "set yrange [0:100]" >> $tmpFile;
  echo -n plot '"'$1client0.cpu.busy.dat'"' title '"'Main client'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.cpu.busy.dat'"' title '"'Remote client $i'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot CPU user/system time
  echo "Generating clients CPU user/system time graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_cpu_user_kernel.$2'"' >> $tmpFile;
  echo 'set title "User/Kernel processor usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Processor usage in %"' >> $tmpFile;
  echo "set yrange [0:100]" >> $tmpFile;
  echo -n plot '"'$1client0.cpu.user.dat'"' title '"'Main client user'"' with lines, '"'$1client0.cpu.system.dat'"' title '"'Main client kernel'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.cpu.user.dat'"' title '"'Remote client $i user'"' with lines', "'$1client$i.cpu.system.dat'"' title '"'Remote client $i system'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot Processes/second
  echo "Generating clients Processes/second graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_procs.$2'"' >> $tmpFile;
  echo 'set title "Processes created"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of processes created per second"' >> $tmpFile;
  echo -n plot '"'$1client0.proc.dat'"' title '"'Main client'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.proc.dat'"' title '"'Remote client $i'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot Context switches/second
  echo "Generating clients Context switches/second graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_ctxtsw.$2'"' >> $tmpFile;
  echo 'set title "Context switches"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of context switches per second"' >> $tmpFile;
  echo -n plot '"'$1client0.ctxsw.dat'"' title '"'Main client'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.ctxsw.dat'"' title '"'Remote client $i'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot Disk total transfers
  echo "Generating clients Disk total transfers graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_disk_tps.$2'"' >> $tmpFile;
  echo 'set title "Disk transfers"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of disk transfers per second"' >> $tmpFile;
  echo -n plot '"'$1client0.disk.tps.dat'"' title '"'Main client'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.disk.tps.dat'"' title '"'Remote client $i'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot disk read/write requests
  echo "Generating clients disk read/write requests graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_disk_rw_req.$2'"' >> $tmpFile;
  echo 'set title "Read/Write disk requests"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of requests per second"' >> $tmpFile;
  echo -n plot '"'$1client0.disk.rtps.dat'"' title '"'Main client read'"' with lines, '"'$1client0.disk.wtps.dat'"' title '"'Main client write'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.disk.rtps.dat'"' title '"'Remote client $i read'"' with lines', "'$1client$i.disk.wtps.dat'"' title '"'Remote client $i write'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot disk blocks read/write requests
  echo "Generating clients disk blocks read/write requests graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_disk_rw_req.$2'"' >> $tmpFile;
  echo 'set title " Disk blocks read/write requests"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of blocks per second"' >> $tmpFile;
  echo -n plot '"'$1client0.disk.brdps.dat'"' title '"'Main client read'"' with lines, '"'$1client0.disk.bwrps.dat'"' title '"'Main client write'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.disk.brdps.dat'"' title '"'Remote client $i read'"' with lines', "'$1client$i.disk.bwrps.dat'"' title '"'Remote client $i write'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot Memory usage
  echo "Generating clients Memory usage graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_mem_usage.$2'"' >> $tmpFile;
  echo 'set title "Memory usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Amount of memory in KB"' >> $tmpFile;
  echo -n plot '"'$1client0.mem.kbmemused.dat'"' title '"'Main client'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.mem.kbmemused.dat'"' title '"'Remote client $i'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot Memory & cache usage
  echo "Generating clients Memory & cache usage graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_mem_cache.$2'"' >> $tmpFile;
  echo 'set title "Memory & cache usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Amount of memory in KB"' >> $tmpFile;
  echo -n plot '"'$1client0.mem.kbmemused.dat'"' title '"'Main client memory'"' with lines, '"'$1client0.mem.kbcached.dat'"' title '"'Main client cache'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.mem.kbmemused.dat'"' title '"'Remote client $i memory'"' with lines', "'$1client$i.mem.kbcached.dat'"' title '"'Remote client $i cache'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot network received/transmitted packets
  echo "Generating clients network received/transmitted packets graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_net_rt_pack.$2'"' >> $tmpFile;
  echo 'set title "Network received/transmitted packets"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of packets per second"' >> $tmpFile;
  echo -n plot '"'$1client0.net.rxpck.dat'"' title '"'Main client received'"' with lines, '"'$1client0.net.txpck.dat'"' title '"'Main client transmitted'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.net.rxpck.dat'"' title '"'Remote client $i received'"' with lines', "'$1client$i.net.txpck.dat'"' title '"'Remote client $i transmitted'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot network received/transmitted bytes
  echo "Generating clients network received/transmitted bytes graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_net_rt_byt.$2'"' >> $tmpFile;
  echo 'set title "Network received/transmitted bytes"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of bytes per second"' >> $tmpFile;
  echo -n plot '"'$1client0.net.rxbyt.dat'"' title '"'Main client received'"' with lines, '"'$1client0.net.txbyt.dat'"' title '"'Main client transmitted'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.net.rxbyt.dat'"' title '"'Remote client $i received'"' with lines', "'$1client$i.net.txbyt.dat'"' title '"'Remote client $i transmitted'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile

  # Plot Sockets usage
  echo "Generating clients Sockets usage graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1client_socks.$2'"' >> $tmpFile;
  echo 'set title "Sockets"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Number of sockets"' >> $tmpFile;
  echo -n plot '"'$1client0.sock.totsck.dat'"' title '"'Main client'"' with lines >> $tmpFile;
  for ((i = 1 ; i < $3 ; i = i + 1)); do
    echo -n ', "'$1client$i.sock.totsck.dat'"' title '"'Remote client $i'"' with lines >> $tmpFile;
  done
  /usr/bin/gnuplot $tmpFile


  #################################
  ## Graphs for CJDBC Controller ##
  #################################
if [ -f $1cjdbc_server.gz ]; then
  # Plot CPU idle time
  echo "Generating CJDBC Server's CPU idle time graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_cpu_idle.$2'"' >> $tmpFile;
  echo 'set title "Processor idle time"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Processor idle time in %"' >> $tmpFile;
  echo "set yrange [0:100]" >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.cpu.idle.dat'"' title '"'CJDBC Server'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot CPU busy time 
  echo "Generating CJDBC Server's CPU busy time graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_cpu_busy.$2'"' >> $tmpFile;
  echo 'set title "Processor usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Processor usage in %"' >> $tmpFile;
  echo "set yrange [0:100]" >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.cpu.busy.dat'"' title '"'CJDBC Server'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot CPU user/system time
  echo "Generating CJDBC Server's CPU user/system time graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_cpu_user_kernel.$2'"' >> $tmpFile;
  echo 'set title "User/Kernel processor usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Processor usage in %"' >> $tmpFile;
  echo "set yrange [0:100]" >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.cpu.user.dat'"' title '"'CJDBC Server user'"' with lines, '"'$1cjdbc_server.cpu.system.dat'"' title '"'CJDBC Server kernel'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Processes/second
  echo "Generating CJDBC Server's Processes/second graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_procs.$2'"' >> $tmpFile;
  echo 'set title "Processes created"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of processes created per second"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.proc.dat'"' title '"'CJDBC Server'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Context switches/second
  echo "Generating CJDBC Server's Context switches/second graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_ctxtsw.$2'"' >> $tmpFile;
  echo 'set title "Context switches"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of context switches per second"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.ctxsw.dat'"' title '"'CJDBC Server'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Disk total transfers
  echo "Generating CJDBC Server's Disk total transfers graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_disk_tps.$2'"' >> $tmpFile;
  echo 'set title "Disk transfers"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of disk transfers per second"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.disk.tps.dat'"' title '"'CJDBC Server'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot disk read/write requests
  echo "Generating CJDBC Server's disk read/write requests graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_disk_rw_req.$2'"' >> $tmpFile;
  echo 'set title "Read/Write disk requests"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of requests per second"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.disk.rtps.dat'"' title '"'CJDBC Server read'"' with lines, '"'$1cjdbc_server.disk.wtps.dat'"' title '"'CJDBC Server write'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot disk blocks read/write requests
  echo "Generating CJDBC Server's disk blocks read/write requests graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_disk_rw_req.$2'"' >> $tmpFile;
  echo 'set title " Disk blocks read/write requests"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of blocks per second"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.disk.brdps.dat'"' title '"'CJDBC Server read'"' with lines, '"'$1cjdbc_server.disk.bwrps.dat'"' title '"'CJDBC Server write'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Memory usage
  echo "Generating CJDBC Server's Memory usage graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_mem_usage.$2'"' >> $tmpFile;
  echo 'set title "Memory usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Amount of memory in KB"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.mem.kbmemused.dat'"' title '"'CJDBC Server'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Memory & cache usage
  echo "Generating CJDBC Server's Memory & cache usage graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_mem_cache.$2'"' >> $tmpFile;
  echo 'set title "Memory & cache usage"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Amount of memory in KB"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.mem.kbmemused.dat'"' title '"'CJDBC Server memory'"' with lines, '"'$1cjdbc_server.mem.kbcached.dat'"' title '"'CJDBC Server cache'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot network received/transmitted packets
  echo "Generating CJDBC Server's network received/transmitted packets graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_net_rt_pack.$2'"' >> $tmpFile;
  echo 'set title "Network received/transmitted packets"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of packets per second"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.net.rxpck.dat'"' title '"'CJDBC Server received'"' with lines, '"'$1cjdbc_server.net.txpck.dat'"' title '"'CJDBC Server transmitted'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot network received/transmitted bytes
  echo "Generating CJDBC Server's network received/transmitted bytes graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_net_rt_byt.$2'"' >> $tmpFile;
  echo 'set title "Network received/transmitted bytes"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Nb of bytes per second"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.net.rxbyt.dat'"' title '"'CJDBC Server received'"' with lines, '"'$1cjdbc_server.net.txbyt.dat'"' title '"'CJDBC Server transmitted'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile

  # Plot Sockets usage
  echo "Generating CJDBC Server's Sockets usage graph";
  echo "set terminal "$2 > $tmpFile;
  echo set output '"'$1cjdbc_server_socks.$2'"' >> $tmpFile;
  echo 'set title "Sockets"' >> $tmpFile;
  echo 'set xlabel "Time in seconds"' >> $tmpFile;
  echo 'set ylabel "Number of sockets"' >> $tmpFile;
  echo -n plot '"'$1cjdbc_server.sock.totsck.dat'"' title '"'CJDBC Server'"' with lines >> $tmpFile;
  /usr/bin/gnuplot $tmpFile
fi


  # Erase data files
  echo "Erasing temporary files ..."
  rm -f $tmpFile $1*.dat

else
  echo "Usage: generate_graphs report_directory/ gnuplot_terminal nb_of_clients"
  echo "Example: generate_graphs 2001-10-15@1:21:39/ gif 2"
fi

