require File.dirname(__FILE__) + "/Cell"


class Grid
	@rows
	@cols

	def initialize(nRow, nCol)
		@rows = (1..nRow).map {
			(1..nCol).map { Cell.new }
		}

		@cols = @rows.transpose
	end

	def copyFrozen
		newG = Grid.new(@rows.size, @cols.size)
		@rows.zip(newG.rows).each {|oldRow, newRow|
			oldRow.zip(newRow).each { |oldCell, newCell|
				newCell.frozenOf(oldCell)
			}
		}

		return newG
	end

	def cellAt(row, col)
		return @rows[row][col]
	end

end
