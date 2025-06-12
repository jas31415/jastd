I started making jastd just for convenience and experience.

I will provide a neat explanation of how this library will function by use of an std::string extension... whenever I get around to that.

Whenever I get a proper version up, I'll add some pre-built releases on the GitHub page.

Using it in a project should hopefully be as simple as adding library and the includes to its directory or integrate them into your own folder structure, and then adding the include path.

This project compiles into a `.dll.a` you will find in the `jastd/bin/` folder, and an executable for unit testing which will be present in `unit_test/bin/`.

If you want to use CMake to compile a project with this, the source code's [CMakeLists.txt](CMakeLists.txt) might be sufficient to explain the requirements, but if it ever becomes necessary I can write a little example application to use as reference.

Another goal is that it should have clear and helpful documentation for all its components inside of the source code (and if possible outside the source code as well).

The name is a blend word of **jas**31415 (that's me, btw) and **std**lib (for standard library) =]
