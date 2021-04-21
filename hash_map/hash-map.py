class _Record():
    def __init__(self, key, value):
        self._key = key
        self._value = value
        self._next = None

    def key(self):
        return self._key

    def value(self):
        return self._value

    def next(self):
        return self._next

    def set_value(self, value):
        self._value = value

    def set_next(self, nxt):
        self._next = nxt


class Hashmap():
    def __init__(self):
        self._store_length = 10
        self._store = [None] * self._store_length

    def set(self, key, value):
        target_record = self._bucket_for(key)

        if target_record is None:
            self._store[key  % self._store_length] = _Record(key, value)
            return

        while True:
            if target_record.key() == key:
                # Update existing.
                target_record.set_value(value)
                return

            nxt = target_record.next()

            if nxt is None:
                target_record.set_next(_Record(key, value))
                return

            target_record = nxt

    def get(self, key):
        target_record = self._bucket_for(key)
        while target_record is not None and target_record.key() != key:
            target_record = target_record.next()

        return target_record.value() if target_record is not None else None

    def _bucket_for(self, key):
        return self._store[key % self._store_length]

    def _resize(self):
        self._store_length *= 2
        old_store = self._store
        self._store = [None] * self._store_length
        for record in old_store:
            if record is None:
                continue
            
            while record is not None:
                self.set(record.key(), record.value())
                record = record.next()


def run_tests():
    hash_map = Hashmap()
    assert hash_map.get(5) == None
    hash_map.set(5, 'a')
    hash_map.set(15, 'b')
    assert hash_map.get(5) == 'a'
    assert hash_map.get(15) == 'b'
    hash_map.set(5, 'c')
    assert hash_map.get(5) == 'c'

    # TODO: Do this conditionally inside of 'set'.
    hash_map._resize()

    assert hash_map.get(5) == 'c'
    assert hash_map.get(15) == 'b'


if __name__ == '__main__':
    run_tests()
