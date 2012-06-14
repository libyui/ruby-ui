class User
  ATTRS = [ :first_name, :surname, :hair, :skill, :beer ]
  ATTRS.each do |attr|
    attr_accessor attr
  end
  def initialize
    ATTRS.each { |a| send :"#{a}=", "" }
  end
end

