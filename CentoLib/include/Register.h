#ifndef REGISTER_H
#define REGISTER_H

extern "C" {
	void libcento_init(size_t hash);
	void libcento_exit(size_t hash);
}

#endif // REGISTER_H