LIBRARIES := libconfigumerator.a
HEADERS := configumerator.h

CXXFLAGS := -std=c++11 -g -Wall -Werror
LDFLAGS := 

all: $(LIBRARIES)

libconfigumerator.a: configumerator.o
	rm -f $@
	ar rcs $@ $^

.libinstall: $(LIBRARIES)
	for lib in $(LIBRARIES); do \
		install $$lib /usr/local/lib; \
	done
	-touch .libinstall

.hdrinstall: $(HEADERS)
	for header in $(HEADERS); do \
		install $$header /usr/local/include; \
	done
	-touch .hdrinstall

install: .libinstall .hdrinstall
