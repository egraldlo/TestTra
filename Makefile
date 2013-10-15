CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =	src/training.o src/producer_consumer.o src/test_theron.o src/test_tree.o \
src/test_daemon.o src/process_fork.o src/exception.o src/effect_cpp.o src/gen_data.o \
src/boost_asio.o src/SChild1.o src/SParent.o src/RegisterChild.o src/BitMap.o \
src/HashTable.o src/Thread_Pool.o src/affinity.o src/processor_num.o src/Barrier.o \
src/BarrierTest.o src/Trees.o src/insert_sort.o src/writter.o src/helloworld.pb.o \
src/readder.o

LIBS = -lboost_serialization -lpthread -ltherond -lboost_system -lboost_thread \
-lboost_regex -lboost_date_time -lprotobuf

TARGET = bin/training

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)