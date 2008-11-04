#!/bin/tcsh

###############################################################################
#
# This script runs first the RUBBoS browsing mix, then the read/write mix 
# for each rubbos.properties_XX specified where XX is the number of emulated
# clients. Note that the rubbos.properties_XX files must be configured
# with the corresponding number of clients.
# In particular set the following variables in rubis.properties_XX:
# httpd_use_version = Servlets
# workload_number_of_clients_per_node = XX/number of client machines
# workload_transition_table = yourPath/RUBBoS/workload/transitions.txt 
#
# This script should be run from the RUBBoS/bench directory on the local 
# client machine. 
# Results will be generated in the RUBBoS/bench directory.
#
################################################################################

setenv SERVLETDIR /users/margueri/RUBBoS/Servlets

# Go back to RUBBoS root directory
cd ..

# Browse only

cp ./workload/browse_only_transitions.txt ./workload/user_transitions.txt
cp ./workload/browse_only_transitions.txt ./workload/author_transitions.txt

foreach i (rubbos.properties_100 rubbos.properties_200 rubbos.properties_300 rubbos.properties_400 rubbos.properties_500 rubbos.properties_600 rubbos.properties_700 rubbos.properties_800 rubbos.properties_900 rubbos.properties_1000) 
  cp bench/$i Client/rubbos.properties
  ssh sci21 -n -l margueri ${SERVLETDIR}/tomcat_stop.sh 
  sleep 4
  ssh sci21 -n -l margueri ${SERVLETDIR}/tomcat_start.sh &
  sleep 4
  bench/flush_cache 490000
  ssh sci23 RUBBoS/bench/flush_cache 880000 	# web server
  ssh sci22 RUBBoS/bench/flush_cache 880000	# database
  ssh sci21 RUBBoS/bench/flush_cache 780000 	# servlet server
  ssh sci6 RUBBoS/bench/flush_cache 490000	# remote client
  ssh sci7 RUBBoS/bench/flush_cache 490000	# remote client
  ssh sci8 RUBBoS/bench/flush_cache 490000	# remote client
  make emulator 
end



# Read/write mix

cp ./workload/user_default_transitions.txt ./workload/user_transitions.txt
cp ./workload/author_default_transitions.txt ./workload/author_transitions.txt

foreach i (rubbos.properties_100 rubbos.properties_200 rubbos.properties_300 rubbos.properties_400 rubbos.properties_500 rubbos.properties_600 rubbos.properties_700 rubbos.properties_800 rubbos.properties_900 rubbos.properties_1000) 
  cp bench/$i Client/rubbos.properties
  ssh sci21 -n -l margueri ${SERVLETDIR}/tomcat_stop.sh 
  sleep 4
  ssh sci21 -n -l margueri ${SERVLETDIR}/tomcat_start.sh &
  sleep 4
  bench/flush_cache 490000
  ssh sci23 RUBBoS/bench/flush_cache 880000 	# web server
  ssh sci22 RUBBoS/bench/flush_cache 880000	# database
  ssh sci21 RUBBoS/bench/flush_cache 780000 	# servlet server
  ssh sci6 RUBBoS/bench/flush_cache 490000	# remote client
  ssh sci7 RUBBoS/bench/flush_cache 490000	# remote client
  ssh sci8 RUBBoS/bench/flush_cache 490000	# remote client
  make emulator
end
