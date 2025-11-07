#ifndef REGISTER_H
#define REGISTER_H

extern "C" {
	void libcento_init(int hash);
	void libcento_exit(int hash);
}

#endif // REGISTER_H