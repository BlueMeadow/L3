load '../Grille/Cellule.rb'
load '../Constants.rb'
#include Comparable


class Grille

	#@param @nbLigne int
	#@param @nbColonne int
  #@param @tabCellules tab[tab[cellule]]

	@nbLigne
	@nbColonne
  @tabCellules
  @pileCoup
  @pileRedo

	attr_accessor :nbLigne, :nbColonne, :tabCellules
	private_class_method :new

    def initialize(nbLigne, nbColonne)
        @nbLigne = nbLigne
        @nbColonne = nbColonne
        @tabCellules = Array.new(nbLigne){|tab|
            tab = Array.new(nbColonne) }
        @pileCoup = Array.new
        @pileRedo = Array.new
    end


    def Grille.creer(nbLigne, nbColonne)
    	new(nbLigne, nbColonne)
    end

    def Grille.copier(grille)
        laCopie = new(grille.nbLigne,grille.nbColonne)
        0.upto(grille.nbLigne-1) { |l|
            0.upto(grille.nbColonne-1) { |c|
                laCopie.tabCellules[l][c] = Cellule.copier(grille.tabCellules[l][c])
            }
        }
        return laCopie

    end

    def ajouterCellule(cellule, posX, posY)
        @tabCellules[posX][posY] = cellule
    end

		def getCellule(x,y)
			return @tabCellules[x][y]
		end

    # Clique glisser avec un clic gauche
    def cliquerGlisserGauche(pos1, pos2, longueur, direction)
        celluleDeDepart = @tabCellules[pos1][pos2]
        coup = Coup.new()
        #On regarde dans quelle direction le drag se fait
        case direction
        	# Drag vers la droite
				when DROITE{
					i = 0
					while i < longueur do
						# On verifie si les cellules sont dans le meme etat que la cellule de depart
						if tabCellules[pos1][i].etat == celluleDeDepart.etat
							# Si oui, on effectue le clic dessus
							coup.ajouter(tabCellules[pos1][i])
							tabCellules[pos1][i].clicGauche
						end
						i+= 1
					end
				}


          # Drag vers le bas
				when BAS{
					i = 0
					while(i < longueur) do
						if(tabCellules[i][pos2].etat == celluleDeDepart.etat)
							tabCellules[i][pos2].clicGauche
							coup.ajouter(tabCellules[pos1][i])
						end
						i+= 1
					end
				}


          # Drag vers la gauche
				when GAUCHE{
					i = longueur-1
					while(i > 0) do
						if(tabCellules[pos1][i].etat == celluleDeDepart.etat)
							tabCellules[pos1][i].clicGauche
							coup.ajouter(tabCellules[pos1][i])
						end
						i-= 1
					end
				}


          # Drag vers le haut
				else
					i = longueur-1
					while(i > 0) do
						if(tabCellules[i][pos2].etat == celluleDeDepart.etat)
							tabCellules[i][pos2].clicGauche
							coup.ajouter(tabCellules[pos1][i])
						end
						i-= 1
					end
        end
        @pileCoup.push(coup)
    end

    # Clique glisser avec un clic droit
    def cliquerGlisserDroit(pos1, pos2, longueur, direction)
        celluleDeDepart = @tabCellules[pos1][pos2]
        coup = Coup.new()
        #On regarde dans quelle direction le drag se fait
        case(direction)
          # Drag vers la droite
          when DROITE
            i = 0
            while(i < longueur)
            	# On verifie si les cellules sont dans le meme etat que la cellule de depart
              if(tabCellules[pos1][i].etat == celluleDeDepart.etat)
                # Si oui, on effectue le clic dessus
                tabCellules[pos1][i].clicDroit
                coup.ajouter(tabCellules[pos1][i])
              end
            	i+=1
            end

          # Drag vers le bas
          when BAS
            i = 0
            while(i < longueur)
              if(tabCellules[i][pos2].etat == celluleDeDepart.etat)
                tabCellules[i][pos2].clicDroit
                coup.ajouter(tabCellules[pos1][i])
              end
              i+=1
            end

          # Drag vers la gauche
          when GAUCHE
            i = longueur-1
            while(i > 0)
              if(tabCellules[pos1][i].etat == celluleDeDepart.etat)
                tabCellules[pos1][i].clicDroit
                coup.ajouter(tabCellules[pos1][i])
              end
              i-=1
						end

            # Drag vers le haut
					else
            i = longueur-1
            while(i > 0)
              if(tabCellules[i][pos2].etat == celluleDeDepart.etat)
                tabCellules[i][pos2].clicDroit
                coup.ajouter(tabCellules[pos1][i])
              end
              i-=1
            end
          end
          @pileCoup.push(coup)
    	end


    def to_s
        s = "Grille : \n["
        @tabCellules.each { |tab|
            s << "["
            tab.each { |cel|
                s << cel.to_s << ","
            }
            s << "]\n"
        }
        return s.chomp << "]"
    end

    def undo
      coup = @pileCoup.pop()
      @pileRedo.push(coup)
      return coup
    end

    def redo
      coup = @pileRedo.pop()
      @pileCoup.push(coup)
      return coup
    end

		def reset
			@pileCoup.clear
			@pileRedo.clear
			@tabCellules.each{ |tab|
				tab.each { |cell|
					cell.reset
				}
			}
		end


		def getLigne(i)
			return @tabCellules[i]
		end

		def getColonne(i)
			tabRes = Array.new
			@tabCellules.each{ |tab|
				tabRes.push(tab[i])
			}
			return tabRes
		end

		#Deux grille sont egales lorsque
		#-Toutes les cases noires de l'une sont noir chez l'autre
		#-Toutes les cases blanches ou croix de l'une sont blanche ou croix sur l'autre
		def equals(autreGrille)
			0.upto(@nbLigne-1) do |i|
				0.upto(@nbColonne-1	) do |j|
					if (!@tabCellules[i][j].equals(autreGrille.tabCellules[i][j]))
						return false
					else
					end
				end
			end
			return true
		end
end


# cellule1 = Cellule.creer(1, true)
# cellule2 = Cellule.creer(1, true)
# cellule3 = Cellule.creer(1, true)
# cellule4 = Cellule.creer(1, true)
#
#
# # Test des cellules
# #puts(cellule4.clicGauche())
# #puts(cellule4.clicDroit())
# #puts(cellule4.clicDroit())
#
#
# #puts(cellule1)
# #puts(cellule1.copier())
#
# #Test de la grille
#
# grille = Grille.creer(2,2)
#
# grille.ajouterCellule(cellule1, 0, 0)
# grille.ajouterCellule(cellule2, 0, 1)
# grille.ajouterCellule(cellule3, 1, 0)
# grille.ajouterCellule(cellule4, 1, 1)
#
# #puts grille
#
# newGrille = Grille.copier(grille)
#
# #puts (newGrille)
#
# cellule2.clicGauche()
#
# puts grille
# puts newGrille
