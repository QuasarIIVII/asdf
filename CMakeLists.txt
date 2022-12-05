project(
	A
	LANGUAGES C
	)
add_compile_options(--static --std=c2x)
add_executable(a a.c)
