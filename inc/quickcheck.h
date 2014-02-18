typedef void* generic_type;
typedef void (*generator)();
typedef int (*validator)(generic_type *);
typedef void (*disposer)(generic_type *);

int for_all(generator generate, validator validate, disposer dispose);
