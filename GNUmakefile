all: generate auto-format compile

generate:
	@python3 build-tools/code-generator/generate.py

compile:
	@mkdir -p build
	@cd build && cmake ..
	@make -C build
clean:
	@rm -rf build
	@rm -rf doc

doc:
	@doxygen build-tools/doc/Doxyfile 

auto-format:
	@find . -type f -name "*.py" |xargs -n1 autopep8 -i
	@find . -type f -name "*.[ch]" |xargs -n1 clang-format -i

