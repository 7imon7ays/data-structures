class MyHashMap

  def initialize(default = nil)
    @default = default
    @num_buckets = 10
    @buckets = Array.new(@num_buckets) { [] }
    @num_elements = 0
  end
  
  def [](el)
    bucket_for(el).each do |key, value|
      return value if key == el
    end
    @default
  end
  
  def []=(el, value)
    @num_elements += 1
    resize if @num_elements.fdiv(@num_buckets) > 0.75
    add(el, value)
  end
  
  private
  
  def bucket_for(el)
    @buckets[el.hash % @num_buckets]
  end
  
  def add(el, value)
    bucket_for(el).each do |kv_pair|
      kv_pair[1] = value && return if kv_pair[0] == el
    end
    .push([el, value])
  end
  
  def resize
    old_buckets = @buckets
    @num_buckets *= 2
    @buckets = Array.new(@num_buckets) { [] }
    old_buckets.each do |bucket|
      bucket.each { |key, value| add(key, value) }
    end
  end
  
end
