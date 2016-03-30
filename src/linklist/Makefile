AR = ar
LIBNAME = linklist

all: $(LIBNAME).a $(LIBNAME).so
	rm $(OBJPATH)/$(LIBNAME).o

$(LIBNAME).a:$(LIBNAME).o
	$(AR) -cr $(STATIC_LIB_PATH)/$@ $(OBJPATH)/$^

$(LIBNAME).so:$(LIBNAME).o
	$(CC) -shared -o $(DYNAMIC_LIB_PATH)/$@ $(OBJPATH)/$^

.c.o:
	$(CC) -fPIC -c $^ -o $(OBJPATH)/$@ $(INCLUDE)
