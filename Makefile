all:
	$(MAKE) -C uploader $@
	$(MAKE) -C loader_kernel $@
	$(MAKE) -C os_kernel $@

%:
	$(MAKE) -C uploader $@
	$(MAKE) -C loader_kernel $@
	$(MAKE) -C os_kernel $@

run:
	$(MAKE) -C os_kernel $@

tidy:
	$(MAKE) -C os_kernel $@

clean:
	$(MAKE) -C uploader $@
	$(MAKE) -C loader_kernel $@
	$(MAKE) -C os_kernel $@