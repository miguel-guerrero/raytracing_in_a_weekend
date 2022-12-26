
dump_rt:
	make -C src ../dump_rt.x
	./dump_rt.x > out.ppm
	if [ `uname` == "Darwin" ]; then \
        open out.ppm ; \
    fi

ez_show_rt:
	make -C src ../ez_show_rt.x
	./ez_show_rt.x

ez_show_rt2:
	make -C src ../ez_show_rt2.x
	./ez_show_rt2.x

ez_show_ppm:
	make -C src ../ez_show_ppm.x
	./ez_show_ppm.x < out.ppm

clean:
	make -C src clean
