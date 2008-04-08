include ../config.mk

####################
#       Client     #
####################

ClientFiles = URLGenerator URLGeneratorServlets URLGeneratorPHP RUBBoSProperties Stats \
	      TransitionTable ClientEmulator UserSession  ../beans/TimeManagement

all_client_sources =  $(addprefix edu/rice/rubbos/client/, $(addsuffix .java, $(ClientFiles)))
all_client_obj = $(addprefix edu/rice/rubbos/client/, $(addsuffix .class, $(ClientFiles)))

client: $(all_client_obj)
	${JAR} cvf rubbos_client.jar $(all_client_obj)

all: client

emulator:
	${JAVA} -Xmx256m -Xms128m -server -classpath . edu.rice.rubbos.client.ClientEmulator

javadoc :
	${MKDIR} -p doc
	${JAVADOC} -d ./doc -bootclasspath ${CLASSPATH} -version -author -windowtitle "RUBBoS Client API" -header "<b>RUBBoS (C)2004 Rice University/INRIA</b><br>"  edu.rice.rubbos.client

clean:
	${RM} -Rf edu/rice/rubbos/client/*.class edu/rice/rubbos/beans/*.class doc/* rubbos_client.jar

