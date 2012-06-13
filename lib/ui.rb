require "ui/version"
require "ui.so"
require 'ui/builder'
require 'ui/event'
require 'ui/dialog'
require 'ui/widget'

module UI

  #
  # @!method self.ask_for_existing_directory(start_dir, headline)
  #
  # Open a directory selection box and prompt the user for an existing
  # directory.
  #
  # @param [String] start_dir the initial directory that is displayed.
  # @param [String] headline an explanatory text for the directory selection box.
  #
  # @example
  #   dir = UI.ask_for_existing_directory(Dir.pwd, "Select a directory")
  #
  # @returns the selected directory name
  #   or an empty string if the user canceled the operation.
  #

  #
  # @!method self.ask_for_existing_file(start_with, headline)
  #
  # Open a file selection box and prompt the user for an existing file.
  #
  # @param [String] start_with is the initial directory or file.
  # @param [String] filter one or more blank-separated file patterns, e.g.
  #   "*.png *.jpg"
  # @param [String] headline' an explanatory text for the file selection box.
  #
  # @return [String] the selected file name
  #   or an empty string if the user canceled the operation.
  #

  #
  # @!method self.ask_for_save_file_name(start_with, filter, headline)
  #
  # Open a file selection box and prompt the user for a file to save data
  # to.  Automatically asks for confirmation if the user selects an existing
  # file.
  #
  # @param [String] start_with is the initial directory or file.
  # @param [String] filter one or more blank-separated file patterns, e.g.
  #   "*.png *.jpg"
  # @param [String] headline' an explanatory text for the file selection box.
  #
  # @return [String] the selected file name
  #   or an empty string if the user canceled the operation.
  #

end