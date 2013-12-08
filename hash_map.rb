class MyHashMap

  def initialize(default = nil)
    @default = default
    @num_buckets = 10
    @buckets = Array.new(@num_buckets) { [] }
    @num_elements = 0
  end
  
  def [](key)
    bucket_for(key).each do |existing_key, value|
      return value if existing_key == key
    end
    @default
  end
  
  def []=(key, value)
    resize if @num_elements.fdiv(@num_buckets) > 0.75
    add(key, value)
    value
  end
  
  private
  
  def bucket_for(key)
    @buckets[key.hash % @num_buckets]
  end
  
  def add(key, value)
    bucket_for(key).each do |kv_pair|
      return kv_pair[1] = value if kv_pair[0] == key
    end << [key, value]
    @num_elements += 1
  end
  
  def resize
    old_buckets = @buckets
    @num_buckets *= 2
    @buckets = Array.new(@num_buckets) { [] }
    old_buckets.each do |bucket|
      bucket.each { |key, value| bucket_for(key) << [key, value] }
    end
  end
  
end
