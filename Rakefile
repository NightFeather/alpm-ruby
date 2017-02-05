require "bundler/gem_tasks"
task :default => :spec

require 'rake/extensiontask'

Rake::ExtensionTask.new "alpm_wrapper" do |ext|
  ext.lib_dir = "lib/alpm_wrapper"
end
