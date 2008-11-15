##############################
#    Environment variables   #
##############################

JAVA_HOME=/usr
JAVA  = $(JAVA_HOME)/bin/java
JAVAC = $(JAVA_HOME)/bin/javac
JAVACC = $(JAVAC) $(JAVACOPTS)
RMIC = $(JAVA_HOME)/bin/rmic
RMIREGISTRY= $(JAVA_HOME)/bin/rmiregistry
CLASSPATH = .:$(J2EE_HOME)/lib/j2ee.jar:$(JAVA_HOME)/jre/lib/rt.jar:/opt/jakarta-tomcat-3.2.3/lib/servlet.jar
JAVADOC = $(JAVA_HOME)/bin/javadoc
JAR = $(JAVA_HOME)/bin/jar

GENIC = ${JONAS_ROOT}/bin/unix/GenIC

MAKE = gmake
CP = /bin/cp
RM = /bin/rm
MKDIR = /bin/mkdir


# EJB server: supported values are jonas or jboss
EJB_SERVER = jonas

# DB server: supported values are MySQL or PostgreSQL
DB_SERVER = MySQL

%.class: %.java
	${JAVACC} -classpath ${CLASSPATH} $<

